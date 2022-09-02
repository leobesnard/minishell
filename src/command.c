/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/02 18:37:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static void	wait_exec(t_cmd_fd *cmd_fd);
static int	exit_exec_error(t_cmd_fd *cmd_fd);

int	execute_command(t_list *parsed, t_env *env)
{
	t_cmd_fd	*cmd_fd;

	cmd_fd = initiate_cmd_fd();
	if (!cmd_fd)
		return (MEM_ERROR);
	while (parsed)
	{
		if (exec_simple_cmd(&parsed, cmd_fd, env) != 0)
			return (exit_exec_error(cmd_fd));
		parsed = parsed->next;
		if (parsed && ((t_cmd *)parsed->content)->type == PIPE_CMD)
			parsed = parsed->next;
	}
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	wait_exec(cmd_fd);
	free(cmd_fd);
	return (0);
}

static void	wait_exec(t_cmd_fd *cmd_fd)
{
	int			i;

	i = 0;
	if (cmd_fd->pid >= 0)
	{
		i = g_minishell.nb_exec;
		waitpid(cmd_fd->pid, &cmd_fd->status, 0);
		while (--i)
			waitpid(-1, NULL, 0);
	}
}

static int	exit_exec_error(t_cmd_fd *cmd_fd)
{
	int	ret;

	ret = cmd_fd->ret;
	if (ret != PIPE_ERROR)
	{
		if (cmd_fd->fd[0] > 2)
			close(cmd_fd->fd[0]);
		if (cmd_fd->fd[1] > 2)
			close(cmd_fd->fd[1]);
	}
	if (cmd_fd->tmp > 2)
		close(cmd_fd->tmp);
	free(cmd_fd);
	return (ret);
}
