/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:03:29 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 22:15:28 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	multiple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env)
{
	char	**argv;
	t_list	*parsed;
	int		ret;

	parsed = *aparsed;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv, env);
	if (cmd_fd->ret < 0)
		return (ret_cmd_not_found(cmd_fd, argv));
	ret = builtin_no_fork_m(cmd_fd, env, argv);
	if (ret < 1)
		return (ret);
	else
		mult_fork(aparsed, cmd_fd, env, argv);
	if (env->flag)
		free(argv[0]);
	free(argv);
	return (0);
}

void	mult_fork(t_list **apsd, t_cmd_fd *cmd_fd, t_env *env, char **argv)
{
	g_minishell.nb_exec++;
	cmd_fd->pid = fork();
	if (cmd_fd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		exec_command(argv, env, apsd, cmd_fd);
		if (cmd_fd->fd[1] > 1)
			close(cmd_fd->fd[1]);
		if (cmd_fd->tmp > 1)
			close(cmd_fd->tmp);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_before_exit(env, argv, cmd_fd);
		exit(0);
	}
}
