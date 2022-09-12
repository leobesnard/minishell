/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:03:11 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/05 14:03:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsed(t_list **parsed)
{
	t_list	*tmp;

	tmp = *parsed;
	while (tmp)
	{
		ft_lstclear(&((t_cmd *)tmp->content)->arg, free);
		ft_lstclear(&((t_cmd *)tmp->content)->rd, free);
		tmp = tmp->next;
	}
	ft_lstclear(parsed, free);
	*parsed = NULL;
}
