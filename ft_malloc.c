/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:57:39 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/16 08:45:49 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_infos    *take_memory_space(size_t size)
{
	t_infos		*zone;

printf("salut\n");
	if (!(zone = mmap(NULL, sizeof(t_infos), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
printf("ca va\n");
    zone->space = mmap(NULL, (size * 100) + 200,
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
printf("bien et toi\n");
    ((unsigned char *)(zone->space))[0] = 'F';
printf("le grand rex\n");
    zone->len = (size * 100) + 20;
printf("zone len = %d\n", (int)zone->len);
	zone->next = NULL;
	return (zone);
}

void    *allocate_memory(t_infos *zone, size_t size)
{
    size_t  check;
    size_t  i;

    i = 0;
	printf("begin allocate memory\n");
    while (i < zone->len)
    {
	printf("debut boucle\n");
        if (((unsigned char *)zone->space)[i] == 'F')
        {
		printf("find F\n");
            check = i + 1;
            while (check < zone->len && check < size)
            {
                if (((unsigned char *)zone->space)[check] == 'A')
                    break ;
                check++;
            }
		printf("check place done\n");
            if (check - i >= size)
            {
			printf("good size find\n");
                ((unsigned char *)zone->space)[i] = 'A';
                ((unsigned char *)zone->space)[i + size] = 0;
                return (zone->space + i + 1);
            }
			i = check; 
        }
		printf("end boucle\n");
        i++;
    }
    return (NULL);
}

void	*search_place_in_page(t_infos *zone, size_t size)
{
	void	*ret;

	ret = NULL;
	if (!zone->space && !(zone = take_memory_space(size)))
		return (NULL);
printf("after take memory\n");
printf("len = %d\n", (int)zone->len);
printf("after checking zone\n");
	while (!(ret = allocate_memory(zone, size)))
	{
	printf("allocate new page\n");
		if (!(zone->next = take_memory_space(size)))
			return (NULL);
	printf("have new page\n");
		zone = zone->next;
	}
printf("ret est bon\n");
	return (ret);
}

void    *malloc(size_t size)
{
    static t_zones  zones;

    if (size <= TINY)
        return (search_place_in_page(&(zones.tiny), size));
    else if (size <= SMALL)
        return (search_place_in_page(&(zones.small), size));
    return (NULL);
}

int     main()
{
    char    *str;

	while ((str = (char *)malloc(30)))
		ft_putendl("momery allocated");
	ft_putendl("\nallocation failed");
    return (0);
}
