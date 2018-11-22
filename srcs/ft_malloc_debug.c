/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:48:28 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/21 22:09:41 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void     vizualise_mem(t_infos *zone, char *name)
{
    size_t  octets;
    size_t  i;
    int     page;

    page = 0;
    printf("%s : %x\n", name, ((unsigned int)zone->space));
    while (zone)
    {
        i = 0;
        printf("page %d : %x\n", page, ((unsigned int)zone->space));
        while (i < zone->len)
        {
            if (((unsigned char *)zone->space)[i] == 'A' && i + 1 < zone->len)
            {
                octets = 0;
                while (i + octets + 1 < zone->len && ((unsigned char *)zone->space)[i + octets + 1] != 'A' &&
                        ((unsigned char *)zone->space)[i + octets + 1] != 'F')
                    octets++;
                if (octets > 0)
                    printf("%lx - %lx : %zu octets\n", ((unsigned int)zone->space) + i,
                            ((unsigned int)zone->space) + i + octets, octets);
                i += octets;
            }
            i++;
        }
        page++;
        zone = zone->next;
    }
}

void            show_alloc_mem()
{
    printf("\nMemory :\n");
    vizualise_mem(g_zones->tiny, "TINY");
    vizualise_mem(g_zones->small, "SMALL");
    if (g_zones->large)
        vizualise_mem(g_zones->large, "LARGE");
    else
        printf("there is no larges zones allocated\n");
    ft_putchar('\n');
    sleep(1);
}