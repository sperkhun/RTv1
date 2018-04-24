/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:15:40 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/23 17:03:15 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *ltl, size_t len)
{
	if (*ltl == '\0')
		return ((char*)big);
	while (len > 0 && *big != '\0')
	{
		if (len >= ft_strlen(ltl) && \
			ft_strncmp(big, ltl, ft_strlen(ltl)) == 0)
			return ((char*)big);
		big++;
		len--;
	}
	return (NULL);
}
