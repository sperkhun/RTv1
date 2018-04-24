/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:25:21 by sperkhun          #+#    #+#             */
/*   Updated: 2017/12/01 14:44:09 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long int	i;
	int					l;

	i = 0;
	l = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			l = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	if (i > 9223372036854775807 && l == -1)
		return (0);
	if (i > 9223372036854775807)
		return (-1);
	return (i * l);
}
