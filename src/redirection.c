/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:19:50 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/14 13:55:58 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd *cmd, t_env *env)
{
	int		ret;
	t_list	*tmp;

	tmp = cmd->rd;
	while (cmd->rd)
	{
		if (((t_token *)cmd->rd->content)->type == GREAT)
		{
			if (rd_great(cmd_fd, &cmd) == FD_ERROR)
				return (FD_ERROR);
		}
		else if (((t_token *)cmd->rd->content)->type == D_GREAT)
		{
			if (rd_d_great(cmd_fd, &cmd) == FD_ERROR)
				return (FD_ERROR);
		}
		else if (((t_token *)cmd->rd->content)->type == LESS)
		{
			if (rd_less(cmd_fd, &cmd) == FD_ERROR)
				return (FD_ERROR);
		}
		else if (((t_token *)cmd->rd->content)->type == D_LESS)
		{
			cmd->rd = cmd->rd->next;
			ret = heredoc(((t_token *)cmd->rd->content)->word, cmd_fd, env);
			if (ret)
				return (ret);
		}
		cmd->rd = cmd->rd->next;
	}
	cmd->rd = tmp;
	return (0);
}

int	rd_great(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd	*cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd_fd->fd[1] == FD_ERROR)
		return (FD_ERROR);
	return (0);
}

int	rd_d_great(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd	*cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd_fd->fd[1] == FD_ERROR)
		return (FD_ERROR);
	return (0);
}

int	rd_less(t_cmd_fd *cmd_fd, t_cmd **acmd)
{
	t_cmd	*cmd;

	cmd = *acmd;
	cmd->rd = cmd->rd->next;
	if (cmd_fd->tmp != 0)
		close(cmd_fd->tmp);
	cmd_fd->tmp = open(((t_token *)cmd->rd->content)->word,
			O_RDONLY, 0777);
	if (cmd_fd->tmp < 0)
		return (FD_ERROR);
	return (0);
}
