/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:17:23 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/06 18:23:30 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg_path(char *arg, char **str);
static int	parse_path_array( char **path_array, char *tmp, char **str);
static char	*concat_path(char *dest, char *src);

int	get_path(char *arg, char **str)
{
	char	**path_array;
	int		ret;
	char	*tmp;

	if (check_arg_path(arg, str) == 0)
		return (0);
	tmp = ft_strdup(arg);
	path_array = ft_split(getenv("PATH"), ':');
	if (!path_array)
		return (MEM_ERROR);
	*str = NULL;
	ret = parse_path_array(path_array, tmp, str);
	if (ret == CMD_NOT_FOUND)
	{
		printf("ret = %d\n", ret);
		free_array(&path_array);
		*str = tmp;
		return (CMD_NOT_FOUND);
	}
	else
		return (ret);
}

static int	check_arg_path(char *arg, char **str)
{
	if (access(arg, X_OK) == 0)
	{
		*str = arg;
		return (0);
	}
	return (1);
}

static int	parse_path_array( char **path_array, char *tmp, char **str)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		*str = concat_path(path_array[i], tmp);
		if (!(*str))
			return (MEM_ERROR);
		if (access(*str, X_OK) == 0)
		{
			free_array(&path_array);
			free(tmp);
			return (0);
		}
		else
			free(*str);
		i++;
	}
	return (CMD_NOT_FOUND);
}

static char	*concat_path(char *dest, char *src)
{
	size_t	len_dest;
	size_t	len_src;
	char	*concat;

	len_dest = ft_strlen(dest) + 1;
	len_src = ft_strlen(src);
	concat = malloc(sizeof(char) * (len_dest + len_src + 1));
	if (!concat)
		return (NULL);
	ft_memcpy(concat, dest, len_dest);
	concat[len_dest - 1] = '/';
	ft_memcpy(concat + len_dest, src, len_src + 1);
	return (concat);
}
