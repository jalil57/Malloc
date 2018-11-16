/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:29:55 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/16 08:45:50 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft/libft.h"
# include <sys/mman.h>

# define TINY   100
# define SMALL  300
# define LARGE  450

typedef struct      s_infos
{
    void            *space;
    size_t          len;
}                   t_infos;

typedef struct      s_zones
{
    t_infos         tiny;
    t_infos         small;
}                   t_zones;

#endif