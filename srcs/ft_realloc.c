/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaibi <jtaibi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:00 by jtaibi            #+#    #+#             */
/*   Updated: 2018/11/20 18:29:54 by jtaibi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void        *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return (NULL);
    if (size <= TINY)
        ;
    if (size <= SMALL)
        ;
    return (NULL);
}