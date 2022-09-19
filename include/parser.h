/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:52 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/19 11:32:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_cmd_type
{
	CMD,
	PIPE_CMD,
	ERR_CMD,
}	t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type	type;
	t_list		*arg;
	t_list		*rd;

}	t_cmd;

//		parser.c

int		check_pipe_slash(t_list *list);
int		parser(t_list *list, t_list **parsed);
int 	fill_cmd(t_list **alist, t_cmd *cmd);
int		fill_cmd_pipe(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type);
int		fill_normal_cmd(t_cmd *cmd, t_list **alst, t_cmd_type cmd_type);
int 	fill_cmd_rd(t_list **alst, t_cmd *cmd);

//		parser_utils.c

int		empty_cmd(t_cmd **cmd);
int		check_all_quotes(t_list *list);
int		check_quotes(t_token *token);
int		exit_cmd(t_list **aparsed, int err_type, int flag, t_cmd *cmd);

#endif
