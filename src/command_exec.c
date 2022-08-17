/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:59:01 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/17 14:38:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	exec_command(char **argv, t_env *env, t_list **aparsed)
{
	printf("arg[0] = %s\n", argv[0]);
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
		builtin_exit(*aparsed);
	else
	{
		execve(argv[0], argv, NULL);
		printf("Execve\n");
	}
	kill(getppid(), SIGKILL);
	perror("execute_command");	
}

int	check_for_builtin(char **argv)
{
	if (!ft_strncmp(argv[0], "echo", 4) || !ft_strncmp(argv[0], "pwd", 3) ||
		!ft_strncmp(argv[0], "unset", 5) || !ft_strncmp(argv[0], "export", 6)
		|| !ft_strncmp(argv[0], "cd", 2) || !ft_strncmp(argv[0], "env", 3) ||
		!ft_strncmp(argv[0], "exit", 4))
		return (1);
	return (0);
}
