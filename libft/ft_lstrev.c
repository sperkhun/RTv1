/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:23:34 by sperkhun          #+#    #+#             */
/*   Updated: 2017/12/02 17:06:54 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **lst)
{
	t_list *add;
	t_list *nxt;

	if (!lst)
		return ;
	add = (*lst)->next;
	(*lst)->next = NULL;
	while (add)
	{
		nxt = add->next;
		ft_lstadd(&(*lst), add);
		add = nxt;
	}
}
