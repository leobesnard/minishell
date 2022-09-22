/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:05 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/22 21:47:27 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *str, int *i)
{
	char	quote_type;

	quote_type = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
	{
		(*i)++;
	}
}

int	init_lexer(t_list **lst, int *flag, char *str)
{
	*lst = NULL;
	if (test_check_quotes(str))
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

int	word(char **str, t_list **token_list)
{
	int	size;

	size = word_size(*str);
	if (!new_node(token_list, *str, size))
		return (free_token_list(token_list), -1);
	*str += size;
	return (0);
}

int	word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_separator(&str[i]) && !is_ws(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_quotes(str, &i);
		i++;
	}
	return (i);
}

int	separator(char **str, t_list **token_list)
{
	int	sep_size;

	sep_size = is_separator(*str);
	if (!new_node(token_list, *str, sep_size))
		return (free_token_list(token_list), -1);
	*str += sep_size;
	return (0);
}
