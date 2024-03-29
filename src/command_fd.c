/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:45:25 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 16:50:58 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	ret_get_args(char ***argv, t_env *env);
static int	check_arg_path(char *arg, char **command_path);

t_cmd_fd	*initiate_cmd_fd(void)
{
	t_cmd_fd	*cmd_fd;

	cmd_fd = malloc(sizeof(t_cmd_fd));
	signal(SIGINT, sigint_child);
	if (!cmd_fd)
		return (NULL);
	cmd_fd->pid = -1;
	cmd_fd->fd[0] = 0;
	cmd_fd->fd[1] = 1;
	cmd_fd->fd_hdoc[0] = 0;
	cmd_fd->fd_hdoc[1] = 1;
	cmd_fd->tmp = 0;
	cmd_fd->status = 42;
	if (!g_minishell.nb_exec)
		g_minishell.nb_exec = 0;
	return (cmd_fd);
}

int	fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed, t_env *env)
{
	int	ret;

	ret = 0;
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	cmd_fd->tmp = cmd_fd->fd[0];
	if (parsed->next)
	{
		if (pipe(cmd_fd->fd) == PIPE_ERROR)
			return (PIPE_ERROR);
	}
	else
		cmd_fd->fd[1] = 1;
	ret = fill_fd_rd(cmd_fd, cmd, env);
	if (ret != 0)
		return (ret);
	if (parsed->next)
		return (2);
	else
		return (1);
}

int	get_args(t_list *list, char ***argv, t_env *env)
{
	int		i;

	*argv = create_args(list);
	if (!(*argv))
		return (MEM_ERROR);
	i = 0;
	while (list)
	{
		(*argv)[i] = ((t_token *)list->content)->word;
		list = list->next;
		i++;
	}
	(*argv)[i] = NULL;
	return (ret_get_args(argv, env));
}

static int	ret_get_args(char ***argv, t_env *env)
{
	char	*command_path;
	int		ret;

	if (check_for_builtin(*argv) == 1)
		return (CMD_BUILTIN);
	else if (check_arg_path((*argv)[0], &command_path) == 1)
		return (CMD_PATH_BINARY);
	if (!(*argv)[0])
		return (0);
	ret = get_path((*argv)[0], &command_path, env);
	if (ret == 0)
		(*argv)[0] = command_path;
	return (ret);
}

static int	check_arg_path(char *arg, char **command_path)
{
	if (access(arg, X_OK) == 0)
	{
		*command_path = arg;
		return (1);
	}
	return (0);
}
