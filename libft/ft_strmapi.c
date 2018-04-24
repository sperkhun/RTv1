/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:26:24 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/15 15:21:57 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			i;
	unsigned int	x;
	char			*a;

	i = 0;
	x = 0;
	if (!s || !f)
		return (NULL);
	a = ft_strnew(ft_strlen(s));
	if (!a)
		return (NULL);
	while (s[i])
	{
		a[i] = f(x, s[i]);
		i++;
		x++;
	}
	return (a);
}
