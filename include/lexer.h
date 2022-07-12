/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:17:39 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/11 17:21:24 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef enum e_token_type
{
	WORD = 0,
	GREAT = 1,
	LESS = 2,
	D_GREAT = 3,
	D_LESS = 4,
	PIPE = 5,
}	t_token_type;

typedef struct s_cmd_line
{
	char		*word;
	struct		cmd_line	*next;
}	t_cmd_line	;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
}	t_token;

t_list	*lexer(char *str);

/* lexer_utils */
void	skip_quotes(char **str);
void	skip_spaces(char **str);

#endif
