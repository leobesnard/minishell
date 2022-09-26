/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:19:50 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/26 21:28:18 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_fd_rd_loop(t_cmd_fd *cmd_fd, t_list **atmp);

int	fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd *cmd, t_env *env)
{
	int		ret;
	t_list	*tmp;

	tmp = cmd->rd;
	while (tmp)
	{
		ret = fill_fd_rd_loop(cmd_fd, &tmp);
		if (((t_token *)tmp->content)->type == D_LESS)
		{
			ret = heredoc(((t_token *)tmp->next->content)->word,
					cmd_fd, env);
			if (ret != 0)
				return (ret);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (ret);
}

static int	fill_fd_rd_loop(t_cmd_fd *cmd_fd, t_list **atmp)
{
	if (((t_token *)(*atmp)->content)->type == GREAT)
	{
		if (rd_great(cmd_fd, atmp) == FD_ERROR)
			return (FD_ERROR);
	}
	else if (((t_token *)(*atmp)->content)->type == D_GREAT)
	{
		if (rd_d_great(cmd_fd, atmp) == FD_ERROR)
			return (FD_ERROR);
	}
	else if (((t_token *)(*atmp)->content)->type == LESS)
	{
		if (rd_less(cmd_fd, atmp) == FD_ERROR)
			return (FD_ERROR);
	}
	return (0);
}

int	rd_great(t_cmd_fd *cmd_fd, t_list **atmp)
{
	t_list	*tmp;

	tmp = *atmp;
	tmp = tmp->next;
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)tmp->content)->word,
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd_fd->fd[1] == FD_ERROR)
		return (FD_ERROR);
	*atmp = (*atmp)->next;
	return (0);
}

int	rd_d_great(t_cmd_fd *cmd_fd, t_list **atmp)
{
	t_list	*tmp;

	tmp = *atmp;
	tmp = tmp->next;
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	cmd_fd->fd[1] = open(((t_token *)tmp->content)->word,
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd_fd->fd[1] == FD_ERROR)
		return (FD_ERROR);
	*atmp = (*atmp)->next;
	return (0);
}

int	rd_less(t_cmd_fd *cmd_fd, t_list **atmp)
{
	t_list	*tmp;

	tmp = *atmp;
	tmp = tmp->next;
	if (cmd_fd->tmp != 0)
		close(cmd_fd->tmp);
	cmd_fd->tmp = open(((t_token *)tmp->content)->word,
			O_RDONLY, 0777);
	if (cmd_fd->tmp < 0)
		return (FD_ERROR);
	*atmp = (*atmp)->next;
	return (0);
}
