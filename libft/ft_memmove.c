/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:33:39 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/07 16:00:22 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((char*)src < (char*)dst)
		while (len--)
			((char*)dst)[len] = ((char*)src)[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
