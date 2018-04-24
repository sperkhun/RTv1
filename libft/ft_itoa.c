/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:23:57 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/15 18:36:03 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		intlen(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int		ifneg(int n)
{
	int neg;

	neg = 0;
	if (n < 0)
		neg = 1;
	return (neg);
}

char			*ft_itoa(int n)
{
	size_t	a;
	int		neg;
	char	*s;

	neg = ifneg(n);
	a = intlen(n) + neg;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = ft_strnew(a);
	if (!s)
		return (NULL);
	if (neg)
	{
		s[0] = '-';
		n = -n;
	}
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--a] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
