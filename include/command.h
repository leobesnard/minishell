/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:09:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/12 17:44:00 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_cmd_fd
{
	int	pid;
	int	status;
	int	fd[2];
	int	tmp;
	int	ret;
}	t_cmd_fd;

typedef struct s_minishell
{
	t_list	*process;
	int		status;
	int		last_exec_code;
}	t_minishell;

typedef struct s_process
{
	pid_t	pid;
	int		status;
}	t_process;

//		command.c

t_cmd_fd	*initiate_cmd_fd(void);
int			fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed);
int			exec_s_command(t_list **aparsed, t_cmd_fd *cmd_fd, char **env, 
		int *nb);
int			execute_command(t_list *parsed);
int			get_args(t_list *list, char ***args);

//		command_utils.c

int			size_list(t_list *list);
char		*concat_path(char *dest, char *src);
int			get_path(char *arg, char **str);
void		free_all_except_one_str(char **array, int x);

//		global.c

int			add_process_to_global(void);
void		finish_job_status();

//		redirection.c

int			fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd	*cmd);
int			rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			exit_exec_error(t_cmd_fd *cmd_fd);

#endif
