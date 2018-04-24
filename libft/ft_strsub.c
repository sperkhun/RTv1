/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:45:27 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/15 15:25:08 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!s)
		return (NULL);
	sub = ft_strnew(len);
	if (!sub)
		return (NULL);
	while (len-- && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}
