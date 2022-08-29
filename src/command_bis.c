/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:05:00 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 14:43:08 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple_cmd(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb)
{
	t_list		*parsed;

	parsed = *aparsed;
	cmd_fd->ret = fill_fd_pipe(cmd_fd, (t_cmd *)parsed->content, parsed);
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (cmd_fd->ret == 1)
	{
		if (one_command(aparsed, cmd_fd, env, nb) != 0)
			return (cmd_fd->ret);
	}
	else
	{
		if (multiple_command(aparsed, cmd_fd, env, nb) != 0)
			return (cmd_fd->ret);
	}
	return (0);
}

int	one_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb)
{
	char	**argv;
	t_list	*parsed;

	parsed = *aparsed;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv);
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (cmd_fd->ret == 1)
		exec_solo_builtin(argv, env, aparsed);
	else
		exec_solo_command(argv, cmd_fd, nb);
	free_array(&argv);
	return (0);
}

int	exec_solo_builtin(char **argv, t_env *env, t_list **apsd)
{
	if (!ft_strncmp(argv[0], "echo", 4))
		builtin_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", 3))
		builtin_pwd(env->envdup);
	else if (!ft_strncmp(argv[0], "unset", 5))
		builtin_unset(env->envdup, argv[1]);
	else if (!ft_strncmp(argv[0], "export", 6))
		builtin_export(env->envdup, argv[1]);
	else if (!ft_strncmp(argv[0], "cd", 2))
		builtin_cd(env->envdup, argv);
	else if (!ft_strncmp(argv[0], "env", 3))
		builtin_env(env->envdup);
	else if (!ft_strncmp(argv[0], "exit", 4))
		builtin_exit(*apsd);
	return (0);
	
}

int	exec_solo_command(char **argv, t_cmd_fd *cmd_fd, int *nb)
{
	cmd_fd->pid = fork();
	if (cmd_fd->pid > 0)
		(*nb)++;
	if (cmd_fd->pid == 0)
	{
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		execve(argv[0], argv, NULL);
		printf("Execve\n");
	}
	return (0);
	
}

int	multiple_command(t_list **aparsed, t_cmd_fd *cmd_fd, t_env *env, int *nb)
{
	char	**argv;
	t_list	*parsed;

	parsed = *aparsed;
	cmd_fd->ret = get_args(((t_cmd *)parsed->content)->arg, &argv);
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	cmd_fd->pid = fork();
	if (cmd_fd->pid > 0)
		(*nb)++;
	if (cmd_fd->pid == 0)
	{
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		exec_command(argv, env, aparsed);
	}
	free_array(&argv);
	return (0);
}
