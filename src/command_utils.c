/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:03:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/27 13:01:06 by rmorel           ###   ########.fr       */
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

void	free_array(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return ;
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
