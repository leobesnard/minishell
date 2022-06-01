/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:59:52 by lbesnard          #+#    #+#             */
/*   Updated: 2022/04/14 19:22:02 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static char	*ft_init_stat(void)
{
	char	*ret;

	ret = malloc(1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

static char	*free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static int	ft_read_file(int fd, char **stat, char *buffer)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while (!ft_strchr(*stat, '\n') && ret != 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		if (ret == 0 && ft_strlen(*stat) == 0)
			return (0);
		buffer[ret] = '\0';
		tmp = *stat;
		*stat = ft_strjoin(*stat, buffer);
		free(tmp);
		if (!*stat)
			return (0);
	}
	return (1);
}

static char	*ft_parser(char **stat)
{
	char	*ret;
	char	*tmp;
	char	*nl;

	if (!stat)
		return (NULL);
	if (!ft_strchr(*stat, '\n'))
	{
		ret = ft_substr(*stat, 0, ft_strlen(*stat));
		if (!ret)
			return (NULL);
		free_ptr(stat);
		return (ret);
	}
	nl = ft_strchr(*stat, '\n') + 1;
	tmp = *stat;
	ret = ft_substr(*stat, 0, nl - *stat);
	*stat = ft_substr(*stat, nl - *stat, ft_strlen(nl));
	free(tmp);
	if (!*stat)
		free_ptr((void *)&ret);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*stat[1024];
	char		*buffer;
	char		*ret;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stat[fd])
	{
		stat[fd] = ft_init_stat();
		if (!stat[fd])
			return (NULL);
	}
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	if (!ft_read_file(fd, &stat[fd], buffer))
	{
		free_ptr((void *)&stat[fd]);
		return (free_ptr((void *)&buffer));
	}
	free(buffer);
	ret = ft_parser(&stat[fd]);
	if (!ret || (stat[fd] && stat[fd][0] == '\0'))
		free_ptr((void *)&stat[fd]);
	return (ret);
}
