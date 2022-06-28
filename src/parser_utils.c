/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:36:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/20 20:17:57 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*empty_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
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
