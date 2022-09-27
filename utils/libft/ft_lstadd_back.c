/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:39:53 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/06 15:13:57 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*newlast;

	if (!new)
		return ;
	newlast = *alst;
	if (!(*alst))
		*alst = new;
	else
	{
		newlast = ft_lstlast(newlast);
		newlast->next = new;
	}
}
