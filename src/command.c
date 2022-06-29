/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/30 00:50:23 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *arg)
{
	char	**path_array;
	char	*str;
	int		i;

	path_array = ft_split(getenv("PATH"), ':');
	if (!path_array)
		return (NULL);
	i = 0;
	str = NULL;
	while (path_array[i])
	{
		str = concat_path(path_array[i], arg);
		if (!str)
			return (NULL);
		if (access(str, X_OK) == 0)
		{
			free_array(path_array);
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	free_all_except_one_str(char **array, int x)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (i != x)
			free(array[i]);
		i++;
	}
	free(array);
	return ;
}

int	fill_fd_rd(t_cmd_fd *cmd_fd, t_cmd	*cmd)
{
	while (cmd->rd)
	{
		if (((t_token *)cmd->rd->content)->type == GREAT)
		{
			cmd->rd = cmd->rd->next;
			close(cmd_fd->fd[1]);
			cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
					O_WRONLY | O_CREAT, 0777);
			if (cmd_fd->fd[1] == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == D_GREAT)
		{
			cmd->rd = cmd->rd->next;
			close(cmd_fd->fd[1]);
			cmd_fd->fd[1] = open(((t_token *)cmd->rd->content)->word,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (cmd_fd->fd[1] == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == LESS)
		{
			cmd->rd = cmd->rd->next;
			close(cmd_fd->fd[2]);
			cmd_fd->fd[2] = open(((t_token *)cmd->rd->content)->word,
					O_RDONLY);
			if (cmd_fd->fd[2] == -1)
				return (-1);
		}
		cmd->rd = cmd->rd->next;
	}
	return (0);
}

t_cmd_fd	*initiate_cmd_fd(void)
{
	t_cmd_fd	*cmd_fd;

	cmd_fd = malloc(sizeof(t_cmd_fd));
	if (!cmd_fd)
		return (NULL);
	cmd_fd->pid = -1;
	cmd_fd->fd[0] = -1;
	cmd_fd->fd[1] = 1;
	cmd_fd->fd[2] = 0;
	return (cmd_fd);
}

int	fill_fd_pipe(t_cmd_fd *cmd_fd, t_cmd *cmd)
{
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->fd[2] > 0)
		close(cmd_fd->fd[2]);
	if (pipe(cmd_fd->fd) == -1)
		return (-1);
	if (fill_fd_rd(cmd_fd, cmd) == -1)
		return (-1);
	return (0);
}

int	execute_command(t_list *parsed)
{
	t_cmd_fd	*cmd_fd;
	t_cmd		*cmd;
	char		**argv;
	char		*newenviron[] = { NULL };
	int			i;

	i = 0;
	cmd_fd = initiate_cmd_fd();
	if (!cmd_fd)
		return (-1);
	while (parsed)
	{
		cmd = (t_cmd *)parsed->content;
		print_cmd_fd(cmd_fd, "After RD");
		if (parsed->next) // If it's not the last command
			fill_fd_pipe(cmd_fd, cmd);
		print_cmd_fd(cmd_fd, "After pipe");
		printf("i = %d\n", ++i);
		argv = get_args(cmd->arg);
		print_tab(argv, "argv");
		cmd_fd->ret = fork();
		if (cmd_fd->ret == 0)
		{
			dup2(cmd_fd->fd[2], 0);
			dup2(cmd_fd->fd[1], 1);
			close(cmd_fd->fd[0]);
			execve(argv[0], argv, newenviron); // Besoin de free apres l'exec ?
			//perror("execve");
		}
		free(argv);
		parsed = parsed->next;
		if (parsed && ((t_cmd *)parsed->content)->type == PIPE_CMD)
			parsed = parsed->next;
	}
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

