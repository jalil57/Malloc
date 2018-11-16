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
#include <stdio.h>

void    take_memory_space(t_infos *zone, size_t size)
{
    zone->space = mmap(NULL, (size * 100) + 200,
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    ((unsigned char *)(zone->space))[0] = 'F';
    zone->len = (size * 100) + 200;
}

void    *allocate_memory(t_infos *zone, size_t size)
{
    size_t  check;
    size_t  i;

    i = 0;
    while (i < zone->len)
    {
        if (((unsigned char *)zone->space)[i] == 'F')
        {
            check = i + 1;
            while (check < zone->len && check < size)
            {
                if (((unsigned char *)zone->space)[check] == 'A')
                    break ;
                check++;
            }
            if (check == size)
            {
                ((unsigned char *)zone->space)[i] = 'A';
                ((unsigned char *)zone->space)[i + size] = 0;
                return (&(zone->space[i + 1]));
            }
        }
        i++;
    }
    return (NULL);
}

void    *malloc(size_t size)
{
    static t_zones  zones;

    if (!(zones.tiny.space))
        take_memory_space(&(zones.tiny), TINY);
    if (!(zones.small.space))
        take_memory_space(&(zones.small), SMALL);
    if (size <= TINY)
        return (allocate_memory(&(zones.tiny), size));
    else if (size <= SMALL)
        return (allocate_memory(&(zones.small), size));
    return (NULL);
}

int     main()
{
    int     i;
    char    *str;

    str = (char *)malloc(30);

    if (!str)
        ft_putendl("return NULL");
    return (0);
}