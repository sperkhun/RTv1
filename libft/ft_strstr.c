/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:41:55 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/06 21:09:48 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *big, const char *little)
{
	size_t i;
	size_t a;

	i = ft_strlen(big);
	a = ft_strlen(little);
	if (!*little)
		return ((char*)big);
	while (*big && a <= i)
	{
		if (!ft_strncmp(big, little, a))
			return ((char*)big);
		big++;
		i--;
	}
	return (NULL);
}
