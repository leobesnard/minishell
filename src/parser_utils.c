/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:36:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/07 18:19:27 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (MEM_ERROR);
	ft_bzero(*cmd, sizeof(t_cmd));
	return (0);
}

int	check_all_quotes(t_list *list)
{
	while (list)
	{
		if (((t_token *)list->content)->type == WORD)
		{
			if (check_quotes((t_token *)list->content) != 0)
				return (-1);
		}
		list = list->next;
	}
	return (0);
}

int	check_quotes(t_token *token)
{
	int		i;
	bool	is_quoted;
	char	quote;

	i = 0;
	is_quoted = false;
	while (token->word[i])
	{
		if (token->word[i] == '"' || token->word[i] == '\'')
		{
			if (is_quoted && token->word[i] == quote)
				is_quoted ^= 1;
			else if (!is_quoted)
			{
				is_quoted ^= 1;
				quote = token->word[i];
			}
		}
		i++;
	}
	if (is_quoted == true)
		return (-1);
	return (0);
}

int	exit_cmd(t_list **parsed, int err_type, int flag, t_cmd *cmd)
{
	t_list	*tmp;

	tmp = NULL;
	while (*parsed)
	{
		ft_lstclear(&((t_cmd *)(*parsed)->content)->arg, free);
		ft_lstclear(&((t_cmd *)(*parsed)->content)->rd, free);
		free((*parsed)->content);
		tmp = (*parsed)->next;
		free(*parsed);
		*parsed = tmp;
	}
	parsed = NULL;
	if (flag == 1)
		free(cmd);
	return (err_type);
}
