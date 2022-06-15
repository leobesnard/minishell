/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/15 16:55:52 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_cmd_list(t_list *list)
{
	t_list			*cmd_lst;
	t_cmd			*cmd;
	t_token			*token;

	if (!list)
		return (NULL);
	cmd_lst = NULL;
	token = (t_token *)list->content;
	while (list)
	{
		cmd = malloc(sizeof(t_node));
		if (!cmd)
			return (NULL);
		ft_bzero(cmd, sizeof(t_node));
		if (fill_cmd(cmd, &list) == -1)
			return (NULL);
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		while (list && token->type != PIPE)
		{
			list = list->next;
			if (list)
				token = (t_token *)list->content;
		}
		if (list)
			list = list->next;
		if (list)
			token = (t_token *)list->content;
	}
	return (cmd_lst);
}

int	fill_cmd(t_cmd *cmd, t_list **alst)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	while (list && (t_token *)(list)->type != PIPE)
	{
		if (list && (((t_token *)content)->type >= 1
					&& ((t_token *)content)->type <= 4))
		{
			ft_lstadd_back(&cmd->rd, ft_lstnew(t_token *)content);
			tmp = list;
			list = list->next;
			ft_lstdelone(tmp, free);
			if (!list || ((t_token *)content)->type != WORD)
				return (-1);
			ft_lstadd_back(&cmd->rd, ft_lstnew(t_token *)content);
			tmp = list;
			list = list->next;
			ft_lstdelone(tmp, free);;
		}
		if (list && ((t_token *)content)->type == WORD)
		{
			ft_lstadd_back(&cmd->arg, ft_lstnew(t_token *)content);
			tmp = list;
			list = list->next;
			ft_lstdelone(tmp, free);
		}
	}
	return (0);
}	
