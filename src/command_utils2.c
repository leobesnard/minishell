/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:54:37 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/23 13:10:16 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_cmd_not_found(t_cmd_fd *cmd_fd, char **argv)
{
	if (argv)
		free(argv);
	return (cmd_fd->ret);
}

void	exit_fork(char **argv, t_cmd_fd *cmd_fd, t_env *env)
{
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	if (argv[0][0] == '/')
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_before_exit(env, argv, cmd_fd);
		exit(126);
	}
	else
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_before_exit(env, argv, cmd_fd);
		exit(127);
	}
}
