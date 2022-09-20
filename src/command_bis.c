/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:05:00 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/20 17:34:03 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	exec_simple_cmd(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env)
{
	t_list		*parsed;

	parsed = *aparsed;
	env->flag = 0;
	printf("%s | ", ((t_token *)((t_cmd *)parsed->content)->arg->content)->word);
	print_cmd_fd(cmd_fd, "before fill_fd_pipe");
	cmd_fd->ret = fill_fd_pipe(cmd_fd, (t_cmd *)parsed->content, parsed, env);
	printf("%s | ", ((t_token *)((t_cmd *)parsed->content)->arg->content)->word);
	print_cmd_fd(cmd_fd, "after fill_fd_pipe");
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (cmd_fd->ret == 1)
	{
		if (one_command(aparsed, cmd_fd, env) != 0)
		{
			return (exit_command(cmd_fd, *aparsed, env));
		}
	}
	else
	{
		if (multiple_command(aparsed, cmd_fd, env) != 0)
			return (exit_command(cmd_fd, *aparsed, env));
	}
	return (0);
}

int	exit_command(t_cmd_fd *cmd_fd, t_list *parsed, t_env *env)
{
	char	*str;
	t_list	*arg;

	arg = ((t_cmd *)parsed->content)->arg;
	str = ((t_token *)arg->content)->word;
	if (cmd_fd->ret != 0)
	{
		if (search_path(env))
			printf("%s: command not found\n", str);
		else
			printf("bash: %s: No such file or directory\n", str);
		g_minishell.last_exec_code = 127;
		return (0);
	}
	return (cmd_fd->ret);
}

int	one_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env)
{
	char	**argv;
	t_list	*parsed;

	parsed = *aparsed;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv, env);
	if (cmd_fd->ret < 0 || !argv[0])
		return (ret_cmd_not_found(cmd_fd, argv));
	if (cmd_fd->ret == 1)
		exec_solo_builtin(argv, env, aparsed, cmd_fd);
	else
		exec_solo_command(argv, cmd_fd, env);
	if (env->flag)
		free(argv[0]);
	free(argv);
	return (0);
}

int	exec_solo_builtin(char **argv, t_env *env, t_list **apsd, t_cmd_fd *cmd_fd)
{
	if (builtin_no_fork(cmd_fd, env, argv, apsd) != 1)
		return (ft_min(cmd_fd->ret, 0));
	else
	{
		cmd_fd->pid = fork();
		g_minishell.nb_exec++;
		if (cmd_fd->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			dup2(cmd_fd->tmp, STDIN_FILENO);
			dup2(cmd_fd->fd[1], STDOUT_FILENO);
			if (cmd_fd->fd[0] != 0)
				close(cmd_fd->fd[0]);
			exec_builtin_fork(cmd_fd, env, argv, &(env->parsed));
			free_before_exit(env, argv, cmd_fd, &(env->parsed));
			exit(0);
		}
	}
	return (0);
}

int	exec_solo_command(char **argv, t_cmd_fd *cmd_fd, t_env *env)
{
	cmd_fd->pid = fork();
	g_minishell.nb_exec++;
	if (cmd_fd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		execve(argv[0], argv, envdup_to_char_array(env));
		exit_fork(argv, cmd_fd, env);
	}
	return (0);
}
