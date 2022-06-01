/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:36:35 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 14:22:34 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	last = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}
