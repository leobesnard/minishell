/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:45:38 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/19 20:48:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *free_token_list(t_list **list)
{
	t_list *tmp;

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

void	free_env(t_list	*env)
{
	t_list	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp);
	}
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
		i++;
	}
	free(*args);
	*args = NULL;
	return ;
}

void	free_parsed(t_list **parsed)
{
	t_list	*tmp;

	tmp = *parsed;
	while (tmp)
	{
		ft_lstclear(&((t_cmd *)tmp->content)->arg, free);
		ft_lstclear(&((t_cmd *)tmp->content)->rd, free);
		tmp = tmp->next;
	}
	ft_lstclear(parsed, free);
	*parsed = NULL;
}
