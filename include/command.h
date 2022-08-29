/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:09:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 15:31:33 by rmorel           ###   ########.fr       */
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

typedef struct s_env
{
	t_list	*envdup;
	char	**envp;
}	t_env;

//		command.c

t_cmd_fd	*initiate_cmd_fd(void);
int			fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed);
int			exec_simple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, 
		int *nb);
int			execute_command(t_list *parsed, t_env *env);
int			get_args(t_list *list, char ***args);

//		command_utils.c

int			size_list(t_list *list);
char		*concat_path(char *dest, char *src);
int			get_path(char *arg, char **str);
void		free_all_except_one_str(char **array, int x);
char		**create_args(t_list *list);

//		global.c

int			add_process_to_global(void);
void		finish_job_status();

//		redirection.c

int			fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd	*cmd);
int			rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			exit_exec_error(t_cmd_fd *cmd_fd);

//		heredoc.c

int			heredoc(char *delimiter, t_cmd_fd *cmd_fd);
char		*heredoc_join(char *s1, char *s2);

//		command_exec.c

void		exec_command(char **argv, t_env *env, t_list **aparsed);
int			check_for_builtin(char **argv);

//		command_bis.c

int	exec_simple_cmd(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb);
int	one_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb);
int	exec_solo_builtin(char **argv, t_env *env, t_list **apsd);
int	exec_solo_command(char **argv, t_cmd_fd *cmd_fd, int *nb);
int	multiple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb);

#endif
