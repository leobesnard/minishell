/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:30:04 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 16:02:24 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!ft_strcmp(var, env->content))
			return (get_var(env->content));
		env = env->next;
	}
	return (NULL);
}

t_list	*del_var(t_list *env, char	*var)
{
	t_list	*tmp;
	t_list	*node;
	char	*before_equal;

	node = env;
	before_equal = find_before_equal(node->content);
	if (!ft_strncmp(before_equal, var, bigger_str(before_equal, var)))
		return (env = env->next, free_node_and_equal(node, before_equal), env);
	to_next_node(&tmp, &node, before_equal);
	while (node)
	{
		before_equal = find_before_equal(node->content);
		if (!ft_strncmp(before_equal, var, bigger_str(before_equal, var)))
		{
			tmp->next = node->next;
			return (free_node_and_equal(node, before_equal), env);
		}
		to_next_node(&tmp, &node, before_equal);
	}
	return (env);
}
