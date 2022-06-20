/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:52 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/20 13:20:49 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H

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

t_list	*create_cmd_list(t_list *list);
t_list	*exit_cmd(t_list *cmd_list);
int		fill_cmd_pipe(t_cmd *cmd, t_list **alst);
int		fill_cmd(t_cmd *cmd, t_list **alst);
int 	fill_cmd_rd(t_list **alst, t_list *tmp, t_cmd *cmd);

//		parser_utils.c

t_cmd	*empty_cmd(void);

#endif
