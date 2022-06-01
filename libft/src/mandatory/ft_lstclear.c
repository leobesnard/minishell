/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:06:35 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/29 15:59:38 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	void	*temp;

	temp = 0;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
