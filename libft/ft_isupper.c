/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:08:06 by sperkhun          #+#    #+#             */
/*   Updated: 2017/12/07 15:09:02 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else
		return (0);
}