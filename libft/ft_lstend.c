/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:25:30 by sperkhun          #+#    #+#             */
/*   Updated: 2017/12/02 16:23:04 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstend(t_list **alst, t_list *new)
{
	t_list *bgn;

	if (!alst || !new)
		return ;
	bgn = *alst;
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = bgn;
}
