/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:05:00 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/13 16:57:37 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	exec_simple_cmd(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env)
{
	t_list		*parsed;

	parsed = *aparsed;
	cmd_fd->ret = fill_fd_pipe(cmd_fd, (t_cmd *)parsed->content, parsed, env);
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (cmd_fd->ret == 1)
	{
		if (one_command(aparsed, cmd_fd, env) != 0)
		{
			return (exit_command(cmd_fd, *aparsed));
		}
	}
	else
	{
		if (multiple_command(aparsed, cmd_fd, env) != 0)
			return (exit_command(cmd_fd, *aparsed));
	}
	return (0);
}

int	exit_command(t_cmd_fd *cmd_fd, t_list *parsed)
{
	char	*str;
	t_list	*arg;

	arg = ((t_cmd *)parsed->content)->arg;
	str = ((t_token *)arg->content)->word;
	if (cmd_fd->ret != 0)
	{
		printf("%s: command not found\n", str);
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
	env->flag = 0;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv, env);
	if (cmd_fd->ret < 0 || !argv[0])
	{
		free(argv);
		return (cmd_fd->ret);
	}
	if (cmd_fd->ret == 1)
		exec_solo_builtin(argv, env, aparsed, cmd_fd);
	else
	{
		exec_solo_command(argv, cmd_fd, env);
	}
//	printf("in command_bis : %s\n", argv[0]);
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
			if (!ft_strncmp(argv[0], "echo", 5))
				builtin_echo(argv);
			else if (!ft_strncmp(argv[0], "pwd", 4))
				builtin_pwd(env->envdup);
			else if (!ft_strncmp(argv[0], "env", 4))
				builtin_env(env->envdup);
			else if (!ft_strncmp(argv[0], "exit", 4))
				builtin_exit(*apsd, env, argv, cmd_fd);
			free_before_exit(env, argv, cmd_fd);
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
		execve(argv[0], argv, env->envp);
		printf("Error execve\n");
	}
	return (0);
}

int	multiple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env)
{
	char	**argv;
	t_list	*parsed;
	int		ret;

	parsed = *aparsed;
	env->flag = 0;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv, env);
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	ret = builtin_no_fork(cmd_fd, env, argv, aparsed);
	if (ret < 1)
		return (ret);
	else
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
			exec_command(argv, env, aparsed, cmd_fd);
			free_before_exit(env, argv, cmd_fd);
			exit(0);
		}
	}
	if (env->flag)
		free(argv[0]);
	free(argv);
	return (0);
}
