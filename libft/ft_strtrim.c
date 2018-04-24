/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:19:16 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/25 18:09:43 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	l;
	size_t	x;
	char	*a;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[l] == ' ' || s[l] == '\n' || s[l] == '\t') && l > i)
		l--;
	a = ft_strnew(l - i + 1);
	if (!a)
		return (NULL);
	while (i <= l && s[i])
	{
		a[x] = s[i];
		x++;
		i++;
	}
	return (a);
}
