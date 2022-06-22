/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:30:04 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/22 23:23:02 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp(const char *s1, const char *s2)
{
	int		i;
	int		n;
	char	*equal;

	i = 0;
	equal = ft_strchr(s2, '=');
	n = equal - s2;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < (n - 1))
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*get_var(char *env_i)
{
	char *equal;

	equal = ft_strchr(env_i, '=') + 1;
	return (equal);
}

t_list	*dup_env(char **envp)
{
	int		i;
	t_list	*env_dup;

	i = 0;
	env_dup = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&env_dup, ft_lstnew(envp[i]));
		i++;
	}
	return (env_dup);
}

char	**add_var(char **env, char *var)
{
	char	*new_var;
	char	**tmp;
	int		i;
	
	i = 0;
	tmp = env;
	while (env[i])
		i++;
	new_var = ft_strdup(var);
	if (!new_var)
		return (NULL);
	env = malloc(sizeof(*env) * (i + 2));
	if (!env)
		return (free_ptr(&new_var));
	i = 0;
	while (tmp[i])
	{
		env[i] = tmp[i];
		i++;
	}
	free_env(tmp);
	env[i] = new_var;
	env[i + 1] = '\0';
	return (env);
}

char	*find_env_var(char **env, char *var)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (!strcmp(var, env[i]))
			return (get_var(env[i]));
		i++;
	}
	return ("variable inexistante\n");
}