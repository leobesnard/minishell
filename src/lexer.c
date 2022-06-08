/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:16:24 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/08 23:33:33 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_separator(char c)
{
	if (c == ' ')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	return (0);
}

t_token_list	*lexer(char *str)
{
	char			*start;
	char			*end;
	t_token_list	*token_list;
	
	bonjour;
	start = str;
	end = str;
	token_list = NULL;
	while (str)
	{
		if (is_separator(end))
			ft_lstadd_back(token_list,
			ft_lstnew(ft_substr(start, start, start - end)));
		if (end == '"' || end == '\'')
			skip_quotes(end);
		else
			start++;
	}
}