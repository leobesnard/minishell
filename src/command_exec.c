/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:59:01 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/12 18:06:49 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	exec_command(char **argv, t_env *env, t_list **aparsed)
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
		builtin_exit(*aparsed, env);
	else
	{
		execve(argv[0], argv, env->envp);
		printf("Execve\n");
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
		builtin_exit(*apsd, env);
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
