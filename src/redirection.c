/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:19:50 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 17:56:47 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd *cmd)
{
	while (cmd->rd)
	{
		if (((t_token *)cmd->rd->content)->type == GREAT)
		{
			if (rd_great(cmd_fd, &cmd) == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == D_GREAT)
		{
			if (rd_d_great(cmd_fd, &cmd) == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == LESS)
		{
			printf("On rentre rd_less\n");
			if (rd_less(cmd_fd, &cmd) == -1)
				return (-1);
		}
		cmd->rd = cmd->rd->next;
	}
	return (0);
}

int	rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd *cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
			O_WRONLY | O_CREAT, 0777);
	if (cmd_fd->fd[1] == -1)
		return (-1);
	return (0);
}

int	rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd	*cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	if (cmd_fd->fd[1] != 1)
		close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd_fd->fd[1] == -1)
		return (-1);
	return (0);
}

int	rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd	*cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	printf("Rd arg = %s\n", ((t_token *)cmd->rd->content)->word);
	if (cmd_fd->tmp != 0)
		close(cmd_fd->tmp);
	cmd_fd->tmp = open(((t_token *)cmd->rd->content)->word,
			O_RDONLY, 0777);
	if (cmd_fd->tmp == -1)
		return (-1);
	return (0);
}
