/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:21:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/08/16 18:14:05 by rmorel           ###   ########.fr       */
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

t_env	*create_struct_env(char **envp)
{
	t_env	*env;

	env = malloc(sizeof(env));
	if (!env)
		return (NULL);
	env->envp = envp;
	env->envdup = dup_env(envp);
	return (env);
}
