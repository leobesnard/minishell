/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/29 10:48:17 by rmorel           ###   ########.fr       */
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

int	fill_cmd_fd(t_cmd_fd *cmd_fd, t_cmd	*cmd)
{
	while (cmd->rd)
	{
		if (((t_token *)cmd->rd->content)->type == GREAT)
		{
			cmd->rd = cmd->rd->next;
			cmd_fd->fdout = open(((t_token *)cmd->rd->content)->word,
					O_WRONLY | O_CREAT, 0777);
			if (cmd_fd->fdout == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == D_GREAT)
		{
			cmd->rd = cmd->rd->next;
			cmd_fd->fdout = open(((t_token *)cmd->rd->content)->word,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (cmd_fd->fdout == -1)
				return (-1);
		}
		else if (((t_token *)cmd->rd->content)->type == LESS)
		{
			cmd->rd = cmd->rd->next;
			cmd_fd->fdin = open(((t_token *)cmd->rd->content)->word,
					O_RDONLY);
			if (cmd_fd->fdin == -1)
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
	cmd_fd->tmpin = dup(0);
	cmd_fd->tmpout = dup(1);
	cmd_fd->fdin = -1;
	cmd_fd->fdout = -1;
	return (cmd_fd);
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
		printf("Debut de boucle\n");
		cmd = (t_cmd *)parsed->content;
		if (fill_cmd_fd(cmd_fd, cmd) == -1)
			return (-1);
		printf("FD before RD: tmpin = %d, tmpout = %d, fdin = %d, fdout = %d\n",
				cmd_fd->tmpin, cmd_fd->tmpout, cmd_fd->fdin, cmd_fd->fdout);
		if (cmd_fd->fdin == -1)
			cmd_fd->fdin = dup(cmd_fd->tmpin);
		if (cmd_fd->fdout == -1)
			cmd_fd->fdout = dup(cmd_fd->tmpout);
		printf("FD after RD : tmpin = %d, tmpout = %d, fdin = %d, fdout = %d\n",
				cmd_fd->tmpin, cmd_fd->tmpout, cmd_fd->fdin, cmd_fd->fdout);
		dup2(cmd_fd->fdin, 0);
		close(cmd_fd->fdin);
		if (cmd->type != PIPE_CMD && parsed->next)
		{
			if (pipe(cmd_fd->fd) == -1)
				return (-1);
			cmd_fd->fdin = cmd_fd->fd[0];
			cmd_fd->fdout = cmd_fd->fd[1];
		}
		dup2(cmd_fd->fdout, 1);
		close(cmd_fd->fdout);
		printf("i = %d\n", ++i);
		if (cmd->type != PIPE_CMD)
		{
			argv = get_args(cmd->arg);
			print_tab(argv, "argv");
			cmd_fd->ret = fork();
			if (cmd_fd->ret == 0)
			{
				execve(argv[0], argv, newenviron);
				//perror("execve");
			}
			free(argv);
		}
		cmd_fd->fdin = -1;
		cmd_fd->fdout = -1;
		parsed = parsed->next;
	}
	dup2(cmd_fd->tmpin, 0);
	dup2(cmd_fd->tmpout, 1);
	close(cmd_fd->tmpin);
	close(cmd_fd->tmpout);
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

