/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:09:20 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 22:34:37 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multi_unset(t_env *env, char **str)
{
	int	i;

	i = 1;
	if (!env->envdup)
		return ;
	while (str[i])
	{
		env->envdup = builtin_unset(env->envdup, str[i]);
		i++;
	}
}

void	multi_export(t_env *env, char **str)
{
	int	i;

	i = 1;
	if (!str)
		return ;
	while (str[i])
	{
		env->envdup = builtin_export(env->envdup, str[i]);
		i++;
	}
}

int	is_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_var_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*find_before_equal(char *str)
{
	char	*equal;
	char	*before_equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	before_equal = ft_substr(str, 0, equal - str);
	if (!before_equal)
		return (NULL);
	return (before_equal);
}
