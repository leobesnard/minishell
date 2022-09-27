/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:59:01 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 17:38:48 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	multi_unset(t_env *env, char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		env->envdup = builtin_unset(env->envdup, str[i]);
		i++;
	}
}

void	exec_command(char **argv, t_env *env, t_list **apsd, t_cmd_fd *cmd_fd)
{
	char	**char_envdup;

	if (!ft_strncmp(argv[0], "echo", 5))
		builtin_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		builtin_pwd(env->envdup);
	else if (!ft_strncmp(argv[0], "unset", 6))
		multi_unset(env, argv);
	else if (!ft_strncmp(argv[0], "export", 7))
		env->envdup = builtin_export(env->envdup, argv, NULL);
	else if (!ft_strncmp(argv[0], "cd", 3))
		builtin_cd(env->envdup, argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		builtin_env(env->envdup);
	else if (!ft_strncmp(argv[0], "exit", 5))
		builtin_exit(*apsd, env, argv, cmd_fd);
	else
	{
		char_envdup = envdup_to_char_array(env);
		execve(argv[0], argv, char_envdup);
		free_array(&char_envdup);
		exit_fork(argv, cmd_fd, env);
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
		multi_unset(env, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 6))
	{
		env->envdup = builtin_export(env->envdup, argv, NULL);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 2))
	{
		builtin_cd(env->envdup, argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "exit", 5))
		builtin_exit(*apsd, env, argv, cmd_fd);
	return (1);
}

int	builtin_no_fork_m(t_cmd_fd *cmd_fd, t_env *env, char **argv)
{
	int	ret;

	if (cmd_fd->ret < 0)
		return (cmd_fd->ret);
	if (!ft_strncmp(argv[0], "unset", 5))
	{
		multi_unset(env, argv);
		free(argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "export", 6))
	{
		env->envdup = builtin_export(env->envdup, argv, NULL);
		free(argv);
		return (0);
	}
	else if (!ft_strncmp(argv[0], "cd", 2))
	{
		ret = builtin_cd(env->envdup, argv);
		free(argv);
		return (ret);
	}
	return (1);
}

int	exec_builtin_fork(t_cmd_fd *cmd_fd, t_env *env, char **argv, t_list **apsd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(argv[0], "echo", 5))
		ret = builtin_echo(argv);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		builtin_pwd(env->envdup);
	else if (!ft_strncmp(argv[0], "env", 4))
		builtin_env(env->envdup);
	else if (!ft_strncmp(argv[0], "exit", 4))
		ret = builtin_exit(*apsd, env, argv, cmd_fd);
	return (ret);
}
