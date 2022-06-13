/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:24 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/13 21:40:18 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_separator(char str)
{
	if (str == ' ')
		return (1);
	if (str == '<')
		return (1);
	if (str == '>')
		return (1);
	return (0);
}

void	skip_quotes(char **str)
{
	char	quote_type;

	quote_type = **str;
	(*str)++;
	while (**str && **str != quote_type)
		(*str)++;
	(*str)--;
}

t_list	*lexer(char *str)
{
	char	*start;
	t_list	*token_list;
	t_token	*token;
	
	start = str;
	token_list = NULL;
	while (*str)
	{
		printf("%c: %d\n", *str, is_separator(*str));
		if (is_separator(*str) || *(str + 1) == '\0')
		{
			token = malloc(sizeof(*token));
			if (!token)
				return (NULL);
			token->word = ft_substr(start, 0, str - start);
			token->type = WORD;
			ft_lstadd_back(&token_list, ft_lstnew(token));
			start = str;
		}
		if (*str == '\'' || *str == '"')
			skip_quotes(&str);
		str++;
	}
	return (token_list);
}
