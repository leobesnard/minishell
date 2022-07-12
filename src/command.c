/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/12 16:12:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_list *parsed)
{
	t_cmd_fd	*cmd_fd;
	char		*env[] = { NULL };
	static int	nb;
	int			i;

	i = 0;
	cmd_fd = initiate_cmd_fd();
	if (!cmd_fd)
		return (MEM_ERROR);
	while (parsed)
	{
		if(exec_s_command(&parsed, cmd_fd, env, &nb) != 0)
			return (exit_exec_error(cmd_fd));
		parsed = parsed->next;
		if (parsed && ((t_cmd *)parsed->content)->type == PIPE_CMD)
			parsed = parsed->next;
	}
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	i = nb;
	waitpid(cmd_fd->pid, &cmd_fd->status, 0);
	while (--i)
		waitpid(-1, NULL, 0);
	free(cmd_fd);
	return (0);
}

t_cmd_fd	*initiate_cmd_fd(void)
{
	t_cmd_fd	*cmd_fd;

	cmd_fd = malloc(sizeof(t_cmd_fd));
	if (!cmd_fd)
		return (NULL);
	cmd_fd->pid = -1;
	cmd_fd->fd[0] = 0;
	cmd_fd->fd[1] = 1;
	cmd_fd->tmp = 0;
	return (cmd_fd);
}

int	exec_s_command(t_list **aparsed, t_cmd_fd *cmd_fd, char **env, int *nb)
{
	t_cmd		*cmd;
	char		**argv;
	t_list		*parsed;
	int			ret;

	parsed = *aparsed;
	cmd = (t_cmd *)parsed->content;
	cmd_fd->ret = fill_fd_pipe(cmd_fd, cmd, parsed);
	if (cmd_fd->ret != 0)
		return (cmd_fd->ret);
	ret = get_args(cmd->arg, &argv);
	if (ret != 0)
		return (ret);
	cmd_fd->pid = fork();
	if (cmd_fd->pid > 0)
		(*nb)++;
	if (cmd_fd->pid == 0)
	{
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		if (add_process_to_global() == MEM_ERROR)
			return (MEM_ERROR);
		execve(argv[0], argv, env);
		perror("execute_command");
	}
	free_array(&argv);
	return (0);
}

int	fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed)
{
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
	if (fill_fd_rd(cmd_fd, cmd) == FD_ERROR)
		return (FD_ERROR);
	return (0);
}

int	exit_exec_error(t_cmd_fd *cmd_fd)
{
	int	ret;

	ret = cmd_fd->ret;
	if (ret != PIPE_ERROR)
	{
		close(cmd_fd->fd[0]);
		close(cmd_fd->fd[1]);
	}
	close(cmd_fd->tmp);
	free(cmd_fd);
	return (ret);
}

int	get_args(t_list *list, char ***argv)
{
	char	*command_path;
	int		i;
	int		ret;

	*argv = malloc(sizeof(**argv) * (size_list(list) + 1));
	if (!(*argv))
		return (MEM_ERROR);
	ft_bzero(*argv, size_list(list) + 1);
	i = 0;
	while (list)
	{
		(*argv)[i] = ft_strdup(((t_token *)list->content)->word);
		list = list->next;
		i++;
	}
	(*argv)[i] = NULL;
	ret = get_path((*argv)[0], &command_path);
	if (ret != 0)
	{
		if ((*argv)[0])
			free_array(argv);
		return (ret);
	}
	(*argv)[0] = command_path;
	return (ret);
}
