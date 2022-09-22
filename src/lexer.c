/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:24 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/22 21:47:51 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ws(char a)
{
	if (a == '\t' || a == '\n' || a == '\r' || a == '\v'
		|| a == '\f' || a == ' ')
		return (1);
	return (0);
}

int	is_separator(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

t_token_type	token_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (D_GREAT);
	if (!ft_strncmp(str, "<<", 2))
		return (D_LESS);
	if (!ft_strncmp(str, "<", 1))
		return (LESS);
	if (!ft_strncmp(str, ">", 1))
		return (GREAT);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	return (0);
}

int	new_node(t_list **token_list, char *start, int size)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (0);
	token->word = ft_substr(start, 0, size);
	if (!token->word)
		return (0);
	token->type = token_type(token->word);
	ft_lstadd_back(token_list, ft_lstnew(token));
	return (1);
}

t_list	*lexer(char *str, int *quote_flag)
{
	char	*start;
	t_list	*token_list;

	if (init_lexer(&token_list, quote_flag, str))
		return (NULL);
	while (*str)
	{
		if (is_ws(*str))
			str++;
		else if (!is_separator(str))
		{
			if (word(&str, &token_list))
				return (NULL);
		}
		else
		{
			if (separator(&str, &token_list))
				return (NULL);
		}
	}
	return (token_list);
}
