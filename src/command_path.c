/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:17:23 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/14 18:49:34 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_path_array( char **path_array, char *dup_arg, char **cmd_pth);
static char	*concat_path(char *dest, char *src);

int	get_path(char *arg, char **command_path, t_env *env)
{
	char	**path_array;
	int		ret;
	char	*dup_arg;

	dup_arg = ft_strdup(arg);
	path_array = ft_split(getenv("PATH"), ':');
	if (!path_array)
		return (free(dup_arg), MEM_ERROR);
	*command_path = NULL;
	env->flag = 1;
	ret = parse_path_array(path_array, dup_arg, command_path);
	if (ret == CMD_NOT_FOUND)
	{
		free_array(&path_array);
		*command_path = dup_arg;
		free(dup_arg);
		return (CMD_NOT_FOUND);
	}
	else
		return (ret);
}

static int	parse_path_array( char **path_array, char *dup_arg, char **cmd_pth)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		*cmd_pth = concat_path(path_array[i], dup_arg);
		if (!(*cmd_pth))
			return (MEM_ERROR);
		if (access(*cmd_pth, X_OK) == 0)
		{
			free_array(&path_array);
			free(dup_arg);
			return (0);
		}
		else
			free(*cmd_pth);
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
