/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:50:48 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/13 14:03:50 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_token *token_list)
{
	t_cmd	*cmd;

	cmd = cmd_new(create_s_cmd(token_list));
	while (token_list->next)
	{
		while (token_list->next && !token_list->type != PIPE)
		{
			token_list = token_list->next;
		}
		if (token_list-next)
		{
			token_list = token_list->next;
			cmd_add_back(cmd_new(create_s_cmd(token_list)));
		}
	}
	return (cmd)
}

t_simple_cmd	*create_s_cmd(t_token *token_list)
{
	t_simple_cmd	*s_cmd;

	if (!token_list)
		return (NULL);
	s_cmd = s_cmd_new(token_list->word);
	while (token_list->next && !token_list->type != PIPE)
	{
		token_list = token_list->next;
		s_cmd_add_back(&s_cmd, s_cmd_new(token_list->word));
	}
	return (s_cmd);
}

void	s_cmd_add_back(t_simple_cmd **alst, t_simple_cmd *lst_new)
{
	t_simple_cmd	*last;

	last = *alst;
	if (!*alst)
	{
		*alst = lst_new;
		return ;
	}
	while (last->next)
		last = last-next;
	last->next = lst_new;
	return ;
}

t_simple_cmd	*s_cmd_new(char *arg)
{
	t_simple_cmd	*s_cmd;

	s_cmd = malloc(sizeof(t_simple_cmd));
	if (!s_cmd)
		return (NULL);
	s_cmd->arg = arg;
	s_cmd->next = NULL;
	return (s_cmd);
}

void	cmd_add_back(t_cmd **alst, t_cmd *lst_new)
{
	t_cmd	*last;

	last = *alst;
	if (!*alst)
	{
		*alst = lst_new;
		return ;
	}
	while (last->next)
		last = last-next;
	last->next = lst_new;
	return ;
}

t_cmd	*cmd_new(t_simple_cmd *s_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->s_cmd = s_cmd;
	cmd->next = NULL;
	return (cmd);
}

