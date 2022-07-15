/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:30:04 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/15 22:15:31 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global_var global;

t_list	*dup_env(char **envp)
{
	int		i;
	char	*content;
	t_list	*env_dup;
	t_list	*new_node;

	i = 0;
	env_dup = NULL;
	while (envp[i])
	{
		content = ft_strdup(envp[i]);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&env_dup, new_node);
		i++;
	}
	return (env_dup);
}

int	add_var(t_list *env, char *var)
{
	char	*content;
	t_list	*new_node;

	content = ft_strdup(var);
	new_node = ft_lstnew(content);
	if (!new_node)
		return (1);
	ft_lstadd_back(&env, new_node);
	return (0);
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
			free(node->content);
			free(node);
			return (env);
		}
		tmp = node;
		node = node->next;
	}
	return (env);
}