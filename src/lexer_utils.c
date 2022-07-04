/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:05 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/28 19:18:06 by lbesnard         ###   ########.fr       */
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

int	is_alpha_spe(int c)
{
	if (c < 40 || c > 126)
	{
		if (c < 35 || c > 38)
		{
			if (c != 33)
				return (0);
		}
	}
	return (1);
}