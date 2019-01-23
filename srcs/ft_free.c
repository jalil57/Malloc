/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:32:46 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/21 15:55:38 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int     search_ptr_in_pages(t_infos *zone, void *ptr)
{
    size_t      i;

    while (zone)
    {
        i = 0;
        while (i < zone->len - 1)
        {
            if (((unsigned char *)(zone->space))[i]== 'A' &&
                    zone->space + i + 1 == ptr)
            {
                ((unsigned char *)(zone->space))[i] = 'F';
                ptr = NULL;
                return (1);
            }
            i++;
        }
        zone = zone->next;
    }
    return (0);
}

static int      search_ptr_in_larges_zones(t_infos *zone, void *ptr)
{
    while (zone)
    {
        if (zone->space + 1 == ptr)
        {
            if (zone->before)
            {
                zone->before->next = zone->next;
                if (zone->next)
                    zone->next->before = zone->before;
            }
            else
            {
                if (zone->next)
                    zone->next->before = NULL;
                g_zones->large = zone->next;
            }
            if (munmap(zone->space, zone->len))
                printf("munmap zone->space failed\n");
            if (munmap(zone, sizeof(t_infos)))
                printf("munmap zone failed\n");
            return (1);
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
    if (search_ptr_in_larges_zones(g_zones->large, ptr))
        return ;
    //que faire si le ptr n'a pas ete alloue ?
}