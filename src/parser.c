/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/01 12:19:05 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_cmd_list(t_list *list, t_list **parsed)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = NULL;
	cmd = NULL;
	if (((t_token *)list->content)->type == PIPE || check_all_quotes(list))
		return (SYNTAX_ERROR);
	while (list)
	{
		if (empty_cmd(&cmd) == MEM_ERROR)
			return (exit_cmd(parsed, MEM_ERROR, 0, cmd));
		if (fill_cmd(&list, cmd) == SYNTAX_ERROR)
			return (exit_cmd(parsed, SYNTAX_ERROR, 1, cmd));
		tmp = ft_lstnew(cmd);
		if (!tmp)
			return (exit_cmd(parsed, MEM_ERROR, 1, cmd));
		ft_lstadd_back(parsed, tmp);
	}
	return (0);
}

int	fill_cmd(t_list **alist, t_cmd *cmd)
{
	t_list	*list;

	list = *alist;
	if (((t_token *)list->content)->type == PIPE)
	{
		if (fill_cmd_pipe(cmd, &list, PIPE_CMD) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
	}
	else if (list)
	{
		if (fill_normal_cmd(cmd, &list, CMD) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
	}
	*alist = list;
	return (0);
}

int	fill_cmd_pipe(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	if (!list->next || ((t_token *)list->next->content)->type == PIPE)
		return (SYNTAX_ERROR);
	tmp = list->next;
	list->next = NULL;
	ft_lstadd_back(&cmd->arg, list);
	list = tmp;
	*alst = list;
	cmd->type = cmd_type;
	return (0);
}

int	fill_normal_cmd(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type)
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
			if (fill_cmd_rd(&list, tmp, cmd) == SYNTAX_ERROR)
				return (SYNTAX_ERROR);
		}
		else
		{
			tmp = list->next;
			list->next = NULL;
			ft_lstadd_back(&cmd->arg, list);
			list = tmp;
		}
	}
	(void) tmp;
	*alst = list;
	cmd->type = cmd_type;
	return (0);
}

int	fill_cmd_rd(t_list **alst, t_list *tmp, t_cmd *cmd)
{
	t_list	*list;

	list = *alst;
	tmp = list->next;
	list->next = NULL;
	ft_lstadd_back(&cmd->rd, list);
	list = tmp;
	if (!list || ((t_token *)list->content)->type != WORD)
		return (SYNTAX_ERROR);
	tmp = list->next;
	list->next = NULL;
	ft_lstadd_back(&cmd->rd, list);
	*alst = tmp;
	return (0);
}
