/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:03:11 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/21 11:50:11 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*free_token_list(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (list)
	{
		if (((t_token *)tmp->content)->word)
			free(((t_token *)tmp->content)->word);
		free(tmp->content);
		tmp = tmp->next;
	}
	*list = tmp;
	return (NULL);
}

char	**free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

void	free_envdup(t_env *env)
{
	t_list	*tmp;

	while (env->envdup)
	{
		tmp = env->envdup;
		env->envdup = env->envdup->next;
		free(tmp->content);
		free(tmp);
	}
	free(env);
}

void	free_node(t_list *node)
{
	free(node);
}

void	free_array(char ***args)
{
	int	i;

	i = 0;
	if (!(*args))
		return ;
	while ((*args)[i])
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
	return ;
}
