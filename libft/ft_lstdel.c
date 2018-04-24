/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:29:27 by sperkhun          #+#    #+#             */
/*   Updated: 2017/11/22 19:16:57 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *n;

	if (!alst || !del)
		return ;
	while (*alst)
	{
		n = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = n;
	}
	*alst = NULL;
}
