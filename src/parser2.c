/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:34:58 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/21 12:35:11 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd(t_list **alist, t_cmd *cmd)
{
	t_list	*list;

	list = *alist;
	if (((t_token *)list->content)->type == PIPE)
	{
		if (fill_cmd_pipe(cmd, &list, PIPE_CMD) == MEM_ERROR)
			return (MEM_ERROR);
	}
	else if (list)
	{
		if (fill_normal_cmd(cmd, &list, CMD) == MEM_ERROR)
			return (MEM_ERROR);
	}
	*alist = list;
	return (0);
}

t_token	*dup_token(t_token *tok)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->word = ft_strdup(tok->word);
	new_token->type = tok->type;
	return (new_token);
}

int	fill_cmd_pipe(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type)
{
	t_list	*list;
	t_token	*tok;

	list = *alst;
	tok = dup_token((t_token *)list->content);
	if (!tok)
		return (MEM_ERROR);
	ft_lstadd_back(&cmd->arg, ft_lstnew(tok));
	list = list->next;
	*alst = list;
	cmd->type = cmd_type;
	return (0);
}

int	fill_normal_cmd(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	while (list && ((t_token *)list->content)->type != PIPE)
	{
		if (list && (((t_token *)list->content)->type >= 1
				&& ((t_token *)list->content)->type <= 4))
		{
			if (fill_cmd_rd(&list, cmd) == MEM_ERROR)
				return (MEM_ERROR);
		}
		else
		{
			tmp = ft_lstnew(dup_token((t_token *)list->content));
			if (!tmp)
				return (MEM_ERROR);
			ft_lstadd_back(&cmd->arg, tmp);
			list = list->next;
		}
	}
	*alst = list;
	cmd->type = cmd_type;
	return (0);
}

int	fill_cmd_rd(t_list **alst, t_cmd *cmd)
{
	t_list	*list;
	t_list	*tmp;

	list = *alst;
	tmp = ft_lstnew(dup_token((t_token *)list->content));
	if (!tmp)
		return (MEM_ERROR);
	ft_lstadd_back(&cmd->rd, tmp);
	list = list->next;
	tmp = ft_lstnew(dup_token((t_token *)list->content));
	if (!tmp)
		return (MEM_ERROR);
	ft_lstadd_back(&cmd->rd, tmp);
	list = list->next;
	*alst = list;
	return (0);
}
