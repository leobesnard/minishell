/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:09:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 17:18:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd_fd
{
	int			pid;
	int			status;
	int			fd[2];
	int			tmp;
}	t_cmd_fd;

//		command.c

t_cmd_fd	*initiate_cmd_fd(void);
int			fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed);
int			exec_s_command(t_list **aparsed, t_cmd_fd *cmd_fd, char **env, 
		int *nb);
int			execute_command(t_list *parsed);
char		**get_args(t_list *list);

//		command_utils.c

int			size_list(t_list *list);
void		free_array(char **args);
char		*concat_path(char *dest, char *src);
char		*get_path(char *arg);
void		free_all_except_one_str(char **array, int x);

//		redirection.c

int			fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd	*cmd);
int			rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd);

#endif
