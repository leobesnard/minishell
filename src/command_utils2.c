/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:54:37 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 17:55:16 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_cmd_not_found(t_cmd_fd *cmd_fd, char **argv)
{
	if (argv)
		free(argv);
	return (cmd_fd->ret);
}

void	exit_fork(char **argv, t_cmd_fd *cmd_fd, t_env *env)
{
	if (cmd_fd->fd[1] > 1)
		close(cmd_fd->fd[1]);
	if (cmd_fd->tmp > 1)
		close(cmd_fd->tmp);
	if (argv[0][0] == '/')
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_before_exit(env, argv, cmd_fd);
		exit(126);
	}
	else
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_before_exit(env, argv, cmd_fd);
		exit(127);
	}
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
