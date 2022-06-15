/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:24 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/15 22:17:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_separator(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (!ft_strncmp(str," ", 1))
		return (1);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, "|", 1))
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
	(*str)++;
}

void	skip_spaces(char **str)
{
	while (**(str) == ' ')
		*(str) += 1;
}

t_token_type token_type(char *str)
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

t_list	*lexer(char *str)
{
	char	*start;
	t_list	*token_list;
	t_token	*token;
	
	start = str;
	token_list = NULL;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			skip_quotes(&str);
		if (is_separator(str) || *(str + 1) == '\0')// || *str == '\0')
		{
			if (*(str + 1) == '\0')
				str++;
			if (start != str)
			{
			token = malloc(sizeof(*token));
			if (!token)
				return (NULL);
			token->word = ft_substr(start, 0, str - start);
			token->type = token_type(token->word);
			ft_lstadd_back(&token_list, ft_lstnew(token));	
			}
			if (*str == ' ')
				skip_spaces(&str);
			start = str;
			printf("start = %c\n", *start);
			if (is_separator(str) && (*str != ' ' && *start != '\0'))
			{
				token = malloc(sizeof(*token));
				if (!token)
					return (NULL);
				token->word = ft_substr(start, 0, is_separator(str));
				token->type = token_type(token->word);
				ft_lstadd_back(&token_list, ft_lstnew(token));
				str += is_separator(str);
			}
			if (*str == ' ')
				skip_spaces(&str);
			start = str;
			printf("start = %c\n", *start);
		}
		while (ft_isalpha(*str) && *(str + 1) != '\0')
			str++;
	}
	return (token_list);
}
