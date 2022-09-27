/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:40:33 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 17:56:28 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	count_line(char *str);
static void	close_fd_hdoc(t_cmd_fd *cmd_fd, t_env *env, char *str);
static void	check_sigint(t_cmd_fd *cmd_fd, t_env *env, char *str);

int	heredoc(char *delimiter, t_cmd_fd *cmd_fd, t_env *env)
{
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	if (cmd_fd->fd_hdoc[0] > 1)
		close(cmd_fd->fd_hdoc[0]);
	if (pipe(cmd_fd->fd_hdoc) == PIPE_ERROR)
		return (PIPE_ERROR);
	cmd_fd->pid = fork();
	if (cmd_fd->pid == 0)
	{
		signal_management(HEREDOC);
		heredoc_fork(cmd_fd, delimiter, env);
	}
	waitpid(cmd_fd->pid, &cmd_fd->status, 0);
	close(cmd_fd->fd_hdoc[1]);
	if (WEXITSTATUS(cmd_fd->status) == 130)
	{
		g_minishell.heredoc = 1;
		close(cmd_fd->fd_hdoc[0]);
		g_minishell.last_exec_code = 130;
		return (SIGINT_HEREDOC);
	}
	cmd_fd->tmp = cmd_fd->fd_hdoc[0];
	return (0);
}

void	heredoc_fork(t_cmd_fd *cmd_fd, char *delimiter, t_env *env)
{
	char	*entry;
	char	*str;

	close(cmd_fd->fd_hdoc[0]);
	str = NULL;
	entry = readline("> ");
	while (ft_strncmp(entry, delimiter, ft_strlen(delimiter) + 1))
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
	check_sigint(cmd_fd, env, str);
	free (entry);
	str = expand(env->envdup, str, &env->quote_flag);
	dup2(cmd_fd->fd_hdoc[1], STDOUT_FILENO);
	printf("%s", str);
	close_fd_hdoc(cmd_fd, env, str);
	close(STDOUT_FILENO);
	exit(0);
}

static void	check_sigint(t_cmd_fd *cmd_fd, t_env *env, char *str)
{
	if (g_minishell.heredoc)
	{
		close_fd_hdoc(cmd_fd, env, str);
		exit(130);
	}
}

static void	close_fd_hdoc(t_cmd_fd *cmd_fd, t_env *env, char *str)
{
	if (cmd_fd->fd_hdoc[1] > 1)
		close(cmd_fd->fd_hdoc[1]);
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->fd[0] > 1)
		close(cmd_fd->fd[0]);
	free_heredoc(env, cmd_fd, str);
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
