/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:21:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/19 16:32:10 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		n;

	i = 0;
	n = ft_strlen(s1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((const char)s1[i] - (const char)s2[i]);
}

char	*get_var(char *env_i)
{
	char *equal;

	equal = ft_strchr(env_i, '=') + 1;
	return (equal);
}

t_env	*create_struct_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->envp = envp;
	env->envdup = dup_env(envp);
	return (env);
}

int	search_path(t_env *env)
{
	t_list	*tmp;

	tmp = env->envdup;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "PATH", 4))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char **envdup_to_char_array(t_env *env)
{
	char	**char_arr;
	int		i;
	t_list	*tmp;

	char_arr = malloc(sizeof(*char_arr) * (size_list(env->envdup) + 1));
	if (!char_arr)
		return (NULL);
	i = 0;
	tmp = env->envdup;
	while (tmp)
	{
		char_arr[i] = strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	char_arr[i] = NULL;
	return (char_arr);
}

char	*get_env_path(t_env *env)
{
	t_list	*tmp;

	tmp = env->envdup;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "PATH", 4))
			return ((char *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
