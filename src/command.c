/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 17:21:01 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd, t_list *parsed)
{
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	cmd_fd->tmp = cmd_fd->fd[0];
	if (parsed->next)
	{
		if (pipe(cmd_fd->fd) == -1)
			return (-1);
	}
	else
		cmd_fd->fd[1] = 1;
	print_cmd_fd(cmd_fd, "After pipe");
	if (fill_fd_rd(cmd_fd, cmd) == -1)
		return (-1);
	return (0);
}

int	exec_s_command(t_list **aparsed, t_cmd_fd *cmd_fd, char **env, int *nb)
{
	t_cmd	*cmd;
	char	**argv;
	t_list	*parsed;

	parsed = *aparsed;
	cmd = (t_cmd *)parsed->content;
	fill_fd_pipe(cmd_fd, cmd, parsed);
	argv = get_args(cmd->arg);
	cmd_fd->pid = fork();
	if (cmd_fd->pid > 0)
		(*nb)++;
	if (cmd_fd->pid == 0)
	{
		dup2(cmd_fd->tmp, STDIN_FILENO);
		dup2(cmd_fd->fd[1], STDOUT_FILENO);
		if (cmd_fd->fd[0] != 0)
			close(cmd_fd->fd[0]);
		execve(argv[0], argv, env);
		perror("execute_command");
	}
	free(argv);
	return (0);
}

int	execute_command(t_list *parsed)
{
	t_cmd_fd	*cmd_fd;
	char		*env[] = { NULL };
	static int	nb;
	int			i;

	i = 0;
	cmd_fd = initiate_cmd_fd();
	if (!cmd_fd)
		return (-1);
	while (parsed)
	{
		exec_s_command(&parsed, cmd_fd, env, &nb);
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
	return (0);
}

char	**get_args(t_list *list)
{
	char	**args;
	char	*command_path;
	int		i;

	args = malloc(sizeof(*args) * (size_list(list) + 1));
	if (!args)
		return (NULL);
	ft_bzero(args, sizeof(list) + 1);
	i = 0;
	while (list)
	{
		args[i] = ft_strdup(((t_token *)list->content)->word);
		list = list->next;
		i++;
	}
	args[i] = NULL;
	command_path = get_path(args[0]);
	if (!command_path)
	{
		free_array(args);
		return (NULL);
	}
	args[0] = command_path;
	return (args);
}
