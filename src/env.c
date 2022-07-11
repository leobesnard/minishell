/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:30:04 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/11 15:11:21 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global_var global;

t_list	*dup_env(char **envp)
{
	int		i;
	t_list	*env_dup;
	t_list	*new_node;

	i = 0;
	env_dup = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		if (!new_node)
			return (NULL);
		//add_trash(&new_node); create add_trash !!!!
		ft_lstadd_back(&env_dup, new_node);
		i++;
	}
	return (env_dup);
}

t_list	*add_var(t_list *env, char *var)
{
	t_list	*new_node;

	new_node = ft_lstnew(var);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(&env, new_node);
	return (env);
}

char	*find_env_var(t_list *env, char *var)
{
	while (env)
	{
		if (!strcmp(var, env->content))
			return (get_var(env->content));
		env = env->next;
	}
	return (NULL);
}

t_list	*del_var(t_list *env, char	*var)
{
	t_list	*tmp;
	t_list	*node;

	node = env;
	if (!strcmp(var, node->content))
	{
		env = env->next;
		return (env);
	}
	tmp = node;
	node = node->next;
	while (node)
	{
		if (!strcmp(var, node->content))
		{
			tmp->next = node->next;
			return (env);
		}
		tmp = node;
		node = node->next;
	}
	return (env);
}