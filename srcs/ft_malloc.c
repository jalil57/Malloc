/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:57:39 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/21 15:49:04 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_infos    *allocate_new_page(size_t size)
{
    size_t      page_size;
	t_infos		*zone;

    if (size > SMALL)
        page_size = size;
    else
        page_size = size <= TINY ? TINY * 4 : SMALL * 4;
	if (!(zone = mmap(NULL, sizeof(t_infos), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
    zone->space = mmap(NULL, page_size,
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    zone->len = page_size;
    ((unsigned char *)(zone->space))[zone->len - 1] = 'A';
    ((unsigned char *)(zone->space))[0] = 'F';
	zone->next = NULL;
    zone->before = NULL;
	return (zone);
}

void        *allocate_memory(t_infos *zone, size_t size)
{
    size_t  check;
    size_t  i;

    i = 0;
    while (i < zone->len)
    {
        if (((unsigned char *)zone->space)[i] == 'F')
        {
            check = 1;
            while (i + check < zone->len && check < size)
            {
                if (((unsigned char *)zone->space)[i + check] == 'A')
                    return (NULL);
                check++;
            }
            if (check == size)
            {
                ((unsigned char *)zone->space)[i] = 'A';
                ((unsigned char *)zone->space)[i + size] = 0;
                if (((unsigned char *)zone->space)[i + size + 1] != 'A')
                    ((unsigned char *)zone->space)[i + size + 1] = 'F';
                return (zone->space + i + 1);
            }
			i = check; 
        }
        i++;
    }
    return (NULL);
}

void	    *search_place_in_page(t_infos *zone, size_t size)
{
	void	*ret;

	while (!(ret = allocate_memory(zone, size)))
	{
		if (!zone->next && !(zone->next = allocate_new_page(size)))
        {
            printf("new page allocation failed\n");
			return (NULL);
        }
        zone->next->before = zone;
		zone = zone->next;
	}
	return (ret);
}

t_zones     *allocate_zones()
{
    t_zones     *zone;

    if (!(zone = mmap(NULL, sizeof(t_zones), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0)))
        return (NULL);
    if (!(zone->tiny = allocate_new_page(TINY)))
        exit(-1);
    if (zone->tiny && !(zone->small = allocate_new_page(SMALL)))
        exit(-1);
    return (zone);
}

void        *allocate_large_space(t_infos **zone, size_t size)
{
    t_infos     *tmp;

    if (!*zone)
    {
        if (!((*zone) = allocate_new_page(size + 2)))
            return (NULL);
        return (allocate_memory(*zone, size));
    }
    tmp = *zone;
    while (tmp->next)
        tmp = tmp->next;
    if (!(tmp->next = allocate_new_page(size + 2)))
        return (NULL);
    tmp->next->before = tmp;
    tmp = tmp->next;
    return (allocate_memory(tmp, size));
}

void        *malloc(size_t size)
{
    if (!size || (!g_zones && !(g_zones = allocate_zones())))
        return (NULL);
    if (size <= TINY)
        return (search_place_in_page(g_zones->tiny, size));
    else if (size <= SMALL)
        return (search_place_in_page(g_zones->small, size));
    return (allocate_large_space(&(g_zones->large), size));
}

int     main()
{
    char    *str1, *str2, *str3, *str4;

    if (!(str1 = (char *)malloc(30)))
        exit(0);
    show_alloc_mem();
    if (!(str2 = (char *)malloc(40)))
        exit(0);
    show_alloc_mem();
    if (!(str3 = (char *)malloc(223)))
        exit(0);
    show_alloc_mem();
    if (!(str4 = (char *)malloc(268)))
        exit(0);
    show_alloc_mem();

    return (0);
}