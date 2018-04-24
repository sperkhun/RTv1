/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:03:23 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/15 15:21:43 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*a;

	i = 0;
	if (!s || !f)
		return (NULL);
	a = ft_strnew(ft_strlen(s));
	if (!a)
		return (NULL);
	while (s[i])
	{
		a[i] = f(s[i]);
		i++;
	}
	return (a);
}
