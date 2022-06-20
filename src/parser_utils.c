/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:36:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/20 15:13:43 by rmorel           ###   ########.fr       */
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

/*
int	check_quotes(t_token *token)
{
	int		i;
	bool	is_quoted;
	char	quote;

	i = 0;
	quote = FALSE;
	if (token->type != WORD)
		return (0);
	while (token->word[i])
	{
		if (token->word[i] == '"' || token->word[i] == ''')
		{
			is_quoted = TRUE;
			quote = token->word[i];
			i++;
			while (token->word[i])
			{
				if (token->word[i] == quote)
				{
					is_quoted = FALSE;
					break;
				}
				i++;
			}
		}
		i++;
	}
	if (is_quoted == TRUE)
		return (-1);
	return (0);
}*/
