/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:03:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/31 17:09:06 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	*concat_path(char *dest, char *src)
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

int	get_path(char *arg, char **str)
{
	char	**path_array;
	int		i;
	char	*tmp;

	if (access(arg, X_OK) == 0)
	{
		*str = arg;
		return (0);
	}
	tmp = ft_strdup(arg);
	free(arg);
	path_array = ft_split(getenv("PATH"), ':');
	if (!path_array)
		return (MEM_ERROR);
	i = 0;
	*str = NULL;
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
	free_array(&path_array);
	free(tmp);
	*str = NULL;
	return (SYNTAX_ERROR);
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

char	**create_args(t_list *list)
{
	char	**args;

	args = malloc(sizeof(char *) * (size_list(list) + 1));
	if (!args)
		return (NULL);
	ft_bzero(args, size_list(list) + 1);
	return (args);
}
