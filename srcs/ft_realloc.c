/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:00 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/21 16:51:04 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int      check_place_after_space(void *ptr, size_t size, size_t len)
{
    size_t  i;

    i = 0;
    while (i < len && i < size)
    {
        if (((unsigned char *)ptr)[i] == 'A')
            return (0);
        i++;
    }
    if (i < size)
        return (0);
    ((unsigned char *)ptr)[i] = 'F';
    return (1);
}

static void     *try_extend_space(t_infos *zone, size_t size, void *ptr)
{
    size_t  i;

    while (zone)
    {
        i = 0;
        while (i < zone->len)
        {
            if (zone->space + i == ptr)
                if (check_place_after_space(ptr + i, size, zone->len - i))
                    return (ptr);
            i++;
        }
        zone = zone->next;
    }
    return (NULL);
}

static void     *search_ptr_in_zones(void *ptr, size_t size)
{
    void    *new_space;

    if ((new_space = try_extend_space(g_zones->tiny, size, ptr)))
        return (new_space);
    if ((new_space = try_extend_space(g_zones->small, size, ptr)))
        return (new_space);
    return (NULL);
}

void            *realloc(void *ptr, size_t size)
{
    void    *new_space;

    if (!ptr)
        return (NULL);
    if (!(new_space = search_ptr_in_zones(ptr, size)))
        return (NULL);
    
    if (!(new_space = malloc(size)))
        return (NULL);

    ;

    return (NULL);
}