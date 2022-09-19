/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:59:01 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/19 15:02:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	exec_command(char **argv, t_env *env, t_list **aparsed, t_cmd_fd *cmd_fd)
{
	if (!ft_strncmp(argv[0], "echo", 5))
		builtin_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		builtin_pwd(env->envdup);
	else if (!ft_strncmp(argv[0], "unset", 6))
		env->envdup = builtin_unset(env->envdup, argv[1]);
	else if (!ft_strncmp(argv[0], "export", 7))
		env->envdup = builtin_export(env->envdup, argv[1]);
	else if (!ft_strncmp(argv[0], "cd", 3))
		builtin_cd(env->envdup, argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		builtin_env(env->envdup);
	else if (!ft_strncmp(argv[0], "exit", 5))
		builtin_exit(*aparsed, env, argv, cmd_fd);
	else
	{
		execve(argv[0], argv, envdup_to_char_array(env));
		if (argv[0][0] == '/')
		{
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_before_exit(env, argv, cmd_fd, &(env->parsed));
			exit(126);
		}
		else
		{
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": Command not found\n", 2);
			free_before_exit(env, argv, cmd_fd, &(env->parsed));
			exit(127);
		}
	}
	return ;
}

int	check_for_builtin(char **argv)
{
	if (!ft_strncmp(argv[0], "echo", 5) || !ft_strncmp(argv[0], "pwd", 4)
		|| !ft_strncmp(argv[0], "unset", 6) || !ft_strncmp(argv[0], "export", 7)
		|| !ft_strncmp(argv[0], "cd", 3) || !ft_strncmp(argv[0], "env", 4)
		|| !ft_strncmp(argv[0], "exit", 5))
		return (1);
	return (0);
}

int	builtin_no_fork(t_cmd_fd *cmd_fd, t_env *env, char **argv, t_list **apsd)
{
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (!ft_strncmp(argv[0], "unset", 5))
	{
		env->envdup = builtin_unset(env->envdup, argv[1]);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 6))
	{
		env->envdup = builtin_export(env->envdup, argv[1]);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 2))
		return (builtin_cd(env->envdup, argv));
	else if (!ft_strncmp(argv[0], "exit", 5))
		builtin_exit(*apsd, env, argv, cmd_fd);
	return (1);
}

int	builtin_no_fork_m(t_cmd_fd *cmd_fd, t_env *env, char **argv)
{
	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (!ft_strncmp(argv[0], "unset", 5))
	{
		env->envdup = builtin_unset(env->envdup, argv[1]);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 6))
	{
		env->envdup = builtin_export(env->envdup, argv[1]);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 2))
		return (builtin_cd(env->envdup, argv));
	return (1);
}
