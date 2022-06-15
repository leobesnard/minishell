/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:50:48 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/13 20:50:38 by rmorel           ###   ########.fr       */
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
	while (list->next && token->type != PIPE)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		ft_bzero(cmd, sizeof(t_cmd));
		if (fill_cmd(cmd, list) == -1)
			return (NULL);
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}

int	fill_cmd(t_cmd *cmd, t_list *list)
{
	int				i;
	t_token_type	tmp_token_rd;
	t_token			*token;
	t_token			*token_next;

	i = 0;
	tmp_token_rd = 0;
	token = (t_token *)list->content;
	while (list && token->type != PIPE)
	{
		while (list && token->type == WORD)
		{
			cmd->arg[i] = ft_strdup(token->word);
			list = list->next;
			token = (t_token *)list->content;
			i++;
		}
		if (list && (token->type >= 1 && token->type <= 4))
		{
			if (!list->next)
				return (-1);
			tmp_token_rd = token->type;
			list = list->next;
			token = (t_token *)list->content;
			token_next = (t_token *)list->next->content;
			if (token->type != WORD)
				return (-1);
			while (list && list->next && token_next->type == WORD)
			{
				list = list->next;
				token_next = (t_token *)list->next->content;
			}
			if (tmp_token_rd == 5 || tmp_token_rd == 7)
				cmd->outfile = ft_strdup(token->word);
			if (tmp_token_rd == 7)
				cmd->append_outfile = 1;
			else if (tmp_token_rd == 6)
				cmd->infile = ft_strdup(token->word);
			list = list->next;
			token = (t_token *)list->content;
		}
	}
	return (0);
}
