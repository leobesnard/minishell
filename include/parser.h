/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:52 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/15 21:25:57 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H

typedef enum e_cmd_type
{
	CMD,
	PIPE_CMD,
}	t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type	type;
	t_list		*arg;
	t_list		*rd;

}	t_cmd;

t_list	*create_cmd_list(t_list *list);
int	fill_cmd_pipe(t_cmd *cmd, t_list **alst);
int	fill_cmd(t_cmd *cmd, t_list **alst);

#endif
