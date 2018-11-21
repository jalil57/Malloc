/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:29:55 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/21 15:22:39 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <sys/mman.h>
#include <stdio.h>

# define TINY   30
# define SMALL  50

typedef struct      s_infos
{
    void            *space;
    size_t          len;
	struct s_infos	*next;
    struct s_infos  *before;
}                   t_infos;

typedef struct      s_zones
{
    t_infos         *tiny;
    t_infos         *small;
    t_infos         *large;
}                   t_zones;

t_zones     *g_zones;

void        free(void *ptr);
void        *realloc(void *ptr, size_t size);
void        show_alloc_mem(void);
void	    *search_place_in_page(t_infos *zone, size_t size);


#endif
