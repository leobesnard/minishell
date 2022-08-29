/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:40:33 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 16:05:36 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delimiter, t_cmd_fd *cmd_fd, t_env *env)
{
	char	*entry;
	char	*str;
	int		n;

	entry = readline("> ");
	str = NULL;
	n = ft_strlen(delimiter);
	while (ft_strncmp(entry, delimiter, n))
	{
		str = heredoc_join(str, entry);
		if (!str)
			return (FD_ERROR);
		if (entry)
			free (entry);
		entry = readline("> ");
	}
	if (entry)
		free (entry);
	cmd_fd->tmp = open("./tmp/heredoc", O_TRUNC | O_WRONLY, 0777);
	if (cmd_fd->tmp == -1)
		return (FD_ERROR);
	str = expand(env->envdup, str);
	write(cmd_fd->tmp, str, ft_strlen(str));
	close(cmd_fd->tmp);
	cmd_fd->tmp = open("./tmp/heredoc", O_RDONLY, 0777);
	return (0);
}

char	*heredoc_join(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!p)
		return (0);
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && s2[n])
	{
		p[i] = s2[n];
		i++;
		n++;
	}
	p[i++] = '\n';
	p[i] = '\0';
	if (s1)
		free (s1);
	return (p);
}
