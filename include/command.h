/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:09:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/08 21:46:28 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define HEREDOC_EOF "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n"

typedef struct s_cmd_fd
{
	int	pid;
	int	status;
	int	fd[2];
	int	fd_hdoc[2];
	int	tmp;
	int	ret;
}	t_cmd_fd;

typedef struct s_minishell
{
	int		nb_exec;
	int		last_exec_code;
	int		heredoc;
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
	t_list	*parsed;
	char	*command_buf;
}	t_env;

typedef struct s_hdocjoin
{
	int		i;
	int		n;
	char	*p;
}	t_hdocjoin;

//		command.c

int			execute_command(t_list *parsed, t_env *env);

//		command_bis.c

int			exec_simple_cmd(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env);
int			one_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env);
int			exec_solo_builtin(char **argv, t_env *env, t_list **apsd,
				t_cmd_fd *cmd_fd);
int			exec_solo_command(char **argv, t_cmd_fd *cmd_fd, t_env *env);
int			multiple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env);

//		command_exec.c

void		exec_command(char **argv, t_env *env, t_list **aparsed);
int			check_for_builtin(char **argv);

//		command_fd.c

t_cmd_fd	*initiate_cmd_fd(void);
int			fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed,
				t_env *env);
int			get_args(t_list *list, char ***args);

//		command_path.c

int			get_path(char *arg, char **str);

//		command_utils.c

int			size_list(t_list *list);
void		free_all_except_one_str(char **array, int x);
char		**create_args(t_list *list);

//		global.c

int			add_process_to_global(void);
void		finish_job_status(void);

//		redirection.c

int			fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd	*cmd, t_env *env);
int			rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd);
int			rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd);

//		heredoc.c

int			heredoc(char *delimiter, t_cmd_fd *cmd_fd, t_env *env);
void		heredoc_fork(t_cmd_fd *cmd_fd, char *delimiter, t_env *env);
char		*heredoc_join(char *s1, char *s2);

#endif
