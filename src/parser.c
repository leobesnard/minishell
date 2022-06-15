/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/15 23:55:17 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_cmd_list(t_list *list)
{
	t_list			*cmd_lst;
	t_cmd			*cmd;

	if (!list)
		return (NULL);
	cmd_lst = NULL;
	if (list && ((t_token *)list->content)->type == PIPE)
		return (NULL);
	while (list)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		ft_bzero(cmd, sizeof(t_cmd));
		if (list && ((t_token *)list->content)->type == PIPE)
		{
			if (fill_cmd_pipe(cmd, &list) == -1)
				return (NULL);
		}
		else if (list)
		{
			cmd->type = CMD;
			if (fill_cmd(cmd, &list) == -1)
				return (NULL);
		}
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}

int	fill_cmd_pipe(t_cmd *cmd, t_list **alst)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	tmp = ft_lstnew((t_token *)list->content);
	if (!tmp)
		return (-1);
	ft_lstadd_back(&cmd->arg, tmp);
	cmd->type = PIPE_CMD;
	tmp = list;
	list = list->next;
	free(tmp);
	return (0);
	*alst = list;
}

int	fill_cmd(t_cmd *cmd, t_list **alst)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	tmp = NULL;
	while (list && ((t_token *)list->content)->type != PIPE)
	{
		if (list && (((t_token *)list->content)->type >= 1
					&& ((t_token *)list->content)->type <= 4))
		{
			tmp = ft_lstnew((t_token *)list->content);
			if (!tmp)
				return (-1);
			ft_lstadd_back(&cmd->rd, tmp);
			tmp = list;
			list = list->next;
			free(tmp);
			if (!list || ((t_token *)list->content)->type != WORD)
				return (-1);
			tmp = ft_lstnew((t_token *)list->content);
			if (!tmp)
				return (-1);
			ft_lstadd_back(&cmd->rd, tmp);
			tmp = list;
			list = list->next;
			free(tmp);
		}
		if (list && ((t_token *)list->content)->type == WORD)
		{
			tmp = ft_lstnew((t_token *)list->content);
			if (!tmp)
				return (-1);
			ft_lstadd_back(&cmd->arg, tmp);
			tmp = list;
			list = list->next;
			free(tmp);
		}
	}
	*alst = list;
	return (0);
}
