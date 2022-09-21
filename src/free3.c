/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:15 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/21 11:50:27 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsed(t_list **parsed)
{
	t_list	*tmp;

	tmp = *parsed;
	while (tmp)
	{
		ft_lstclear(&((t_cmd *)tmp->content)->arg, &free_token);
		ft_lstclear(&((t_cmd *)tmp->content)->rd, &free_token);
		tmp = tmp->next;
	}
	ft_lstclear(parsed, free);
	*parsed = NULL;
}
