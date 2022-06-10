/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:36:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/13 12:39:01 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
} PAS SUR QUE CE SOIT UTILE, CME FT_LSTADDBACK*/

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

/*
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
} IDEM*/

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
