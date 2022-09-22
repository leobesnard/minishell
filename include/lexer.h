/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:17:39 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/22 21:47:21 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	char			*word;
	struct cmd_line	*next;
}	t_cmd_line;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
}	t_token;

t_list			*lexer(char *str, int *quote_flag);
int				is_separator(char *str);
int				new_node(t_list **token_list, char *start, int size);
t_token_type	token_type(char *str);
int				is_ws(char a);

/* lexer_utils */
void			skip_quotes(char *str, int *i);
int				separator(char **str, t_list **token_list);
int				init_lexer(t_list **lst, int *flag, char *str);
int				word(char **str, t_list **token_list);
int				word_size(char *str);

#endif
