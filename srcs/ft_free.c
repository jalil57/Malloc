/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:32:46 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/20 17:59:40 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int     search_ptr_in_pages(t_infos *zone, void *ptr)
{
    size_t      i;

    while (zone)
    {
        i = 0;
        while (i < zone->len)
        {
            if (zone->space + i == ptr)
            {
                ((unsigned char *)(zone->space))[i] = 'F';
                return (1);
            }
            i++;
        }
        zone = zone->next;
    }
    return (0);
}

void            free(void *ptr)
{
    if (!ptr)
        return ;
    if (search_ptr_in_pages(g_zones->tiny, ptr))
        return ;
    if (search_ptr_in_pages(g_zones->small, ptr))
        return ;
}