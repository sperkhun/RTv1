/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:13:43 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/06 20:14:24 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)malloc(sizeof(*str) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (i <= ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
