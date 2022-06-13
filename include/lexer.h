/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:17:39 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/09 18:08:09 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include "libft.h"

typedef enum e_token_type
{
	NONE,
	WORD,
	R_RD,
	L_RD,
	DR_RD,
	DL_RD,
}	t_token_type;

typedef struct s_cmd_line
{
	char	*word;
	struct cmd_line	*next;
}	t_cmd_line;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
}	t_token;

/* lexer */
t_list	*lexer(char *str);


#endif