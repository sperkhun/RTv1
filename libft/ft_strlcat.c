/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 18:32:58 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/08 16:47:03 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t d;

	i = 0;
	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + size);
	while (dst[i] && i < size)
		i++;
	d = i;
	while (src[i - d] && i < size - 1)
	{
		dst[i] = src[i - d];
		i++;
	}
	dst[i] = '\0';
	return (d + ft_strlen(src));
}
