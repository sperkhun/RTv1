/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:53:41 by sperkhun          #+#    #+#             */
/*   Updated: 2017/12/01 14:39:19 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		wrd_len(const char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

static char		*words(const char **s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = ft_strnew(wrd_len(*s, c));
	if (!str)
		return (NULL);
	while (**s != c && **s != '\0')
	{
		str[i] = **s;
		i++;
		*s += 1;
	}
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	wrd;
	char	**str;

	i = 0;
	wrd = ft_cntwrd(s, c);
	if (!s || !(str = (char**)malloc(sizeof(*str) * (wrd + 1))))
		return (NULL);
	while (i < wrd && *s)
	{
		while (*s == c && *s)
			s++;
		str[i] = words(&s, c);
		if (!str[i])
		{
			ft_arrdel(str, i);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
