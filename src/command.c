/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/28 14:57:27 by rmorel           ###   ########.fr       */
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


int	execute_command(t_list *parsed)
{
	int		tmp_in;
	int		tmp_out;
	int		fdin;
	int		fdout;
	int		fd[2];
	t_cmd	*cmd;
	int		ret;
	char	**argv;
	char	*newenviron[] = { NULL };

	tmp_in = dup(0);
	tmp_out = dup(1);
	fdin = -1;
	fdout = -1;
	while (parsed)
	{
		cmd = (t_cmd *)parsed->content;
		while (cmd->rd)
		{
			if (((t_token *)cmd->rd->content)->type == GREAT)
			{
				cmd->rd = cmd->rd->next;
				fdout = open(((t_token *)cmd->rd->content)->word, O_WRONLY | O_CREAT, 0777);
				if (fdout == -1)
					return (-1);
			}
			else if (((t_token *)cmd->rd->content)->type == D_GREAT)
			{
				cmd->rd = cmd->rd->next;
				fdout = open(((t_token *)cmd->rd->content)->word, O_WRONLY | O_CREAT | O_APPEND, 0777);
				if (fdout == -1)
					return (-1);
			}
			else if (((t_token *)cmd->rd->content)->type == LESS)
			{
				cmd->rd = cmd->rd->next;
				fdin = open(((t_token *)cmd->rd->content)->word, O_RDONLY);
				if (fdin == -1)
				{
					printf("< non trouve, fin boucle\n");
					return (-1);
				}
			}
			cmd->rd = cmd->rd->next;
		}
		if (fdin == -1)
			fdin = dup(tmp_in);
		if (fdout == -1)
			fdout = dup(tmp_out);
		printf("tmpin = %d, tmpout = %d, fdin = %d, fdout = %d\n", tmp_in, tmp_out, fdin, fdout);
		dup2(fdin, 0);
		close(fdin);
		dup2(fdout, 1);
		close(fdout);
		if (cmd->type != PIPE_CMD && parsed->next)
		{
			pipe(fd);
			fdin = fd[0];
			fdout = fd[1];
		}
		if (cmd->type != PIPE_CMD)
		{
			argv = get_args(cmd->arg);
			ret = fork();
			if (ret == 0)
			{
				execve(argv[0], argv, newenviron);
				//perror("execve");
			}
			free(argv);
		}
		fdin = -1;
		fdout = -1;
		parsed = parsed->next;
	}
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	close(tmp_in);
	close(tmp_out);
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

