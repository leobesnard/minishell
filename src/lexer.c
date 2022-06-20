/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:24 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/20 17:47:49 by lbesnard         ###   ########.fr       */
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

/* void	fill_list(t_list **token_list, char **str, char **start)
{
	if (**(str + 1) == '\0' && **str != ' ')
		*str++;
	if (*start != *str)
	{
		if (!new_node(&token_list, *start, *str - *start))
			return (free_list(&token_list));
	}
	if (**str == ' ')
		skip_spaces(str);
	*start = *str;
	if (is_separator(*str) && (*str != ' ' && *start != '\0'))
	{
		if (!new_node(&token_list, start, is_separator(str)))
			return (free_list(&token_list));
		str += is_separator(str);
	}
	if (*str == ' ')
		skip_spaces(&str);
	start = str;
} */

t_list	*lexer(char *str)
{
	char	*start;
	t_list	*token_list;
	
	start = str;
	token_list = NULL;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			skip_quotes(&str);
		if (is_separator(str) || *(str + 1) == '\0')
		{
			if (*(str + 1) == '\0' && *str != ' ')
				str++;
			if (start != str)
			{
				if (!new_node(&token_list, start, str - start))
					return (free_list(&token_list));
			}
			if (*str == ' ')
				skip_spaces(&str);
			start = str;
			if (is_separator(str) && (*str != ' ' && *start != '\0'))
			{
				if (!new_node(&token_list, start, is_separator(str)))
					return (free_list(&token_list));
				str += is_separator(str);
			}
			if (*str == ' ')
				skip_spaces(&str);
			start = str;
		}
		while (ft_isalpha(*str) && *(str + 1) != '\0')
			str++;
	}
	return (token_list);
}
