/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:05 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/20 16:42:51 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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