/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:03:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/05 12:36:43 by rmorel           ###   ########.fr       */
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

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
