/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:40:33 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/20 17:01:05 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	count_line(char *str);

int	heredoc(char *delimiter, t_cmd_fd *cmd_fd, t_env *env)
{
	if (cmd_fd->tmp > 0)
		close(cmd_fd->tmp);
	if (pipe(cmd_fd->fd_hdoc) == PIPE_ERROR)
		return (PIPE_ERROR);
	cmd_fd->pid = fork();
	if (cmd_fd->pid == 0)
		heredoc_fork(cmd_fd, delimiter, env);
	waitpid(cmd_fd->pid, &cmd_fd->status, 0);
	close(cmd_fd->fd_hdoc[1]);
	cmd_fd->tmp = cmd_fd->fd_hdoc[0];
	return (0);
}

void	heredoc_fork(t_cmd_fd *cmd_fd, char *delimiter, t_env *env)
{
	char	*entry;
	char	*str;

	signal_management(HEREDOC);
	close(cmd_fd->fd_hdoc[0]);
	str = NULL;
	entry = readline("> ");
	while (ft_strncmp(entry, delimiter, ft_strlen(delimiter)))
	{
		if (!entry || g_minishell.heredoc)
			break ;
		str = heredoc_join(str, entry);
		if (entry)
			free (entry);
		entry = readline("> ");
	}
	if (!entry && !g_minishell.heredoc)
		printf(HEREDOC_EOF, count_line(str), delimiter);
	free (entry);
	str = expand(env->envdup, str, &env->quote_flag);
	dup2(cmd_fd->fd_hdoc[1], STDOUT_FILENO);
	printf("%s", str);
	close(cmd_fd->fd_hdoc[1]);
	free_heredoc(env, cmd_fd, str);
	exit(0);
}

char	*heredoc_join(char *s1, char *s2)
{
	t_hdocjoin	hd;

	hd.i = 0;
	hd.n = 0;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	hd.p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!hd.p)
		return (NULL);
	while (s1 && s1[hd.i])
	{
		hd.p[hd.i] = s1[hd.i];
		hd.i++;
	}
	while (s2 && s2[hd.n])
	{
		hd.p[hd.i] = s2[hd.n];
		hd.i++;
		hd.n++;
	}
	hd.p[hd.i++] = '\n';
	hd.p[hd.i] = '\0';
	if (s1)
		free (s1);
	return (hd.p);
}

static int	count_line(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (!str)
		return (count);
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}
