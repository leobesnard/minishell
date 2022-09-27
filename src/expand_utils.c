/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:37:10 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 14:13:46 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incr(char *str, t_vars *var)
{
	var->ret[var->u] = str[var->i];
	var->u++;
	var->i++;
}

void	var_incr(t_var *var)
{
	var->sz++;
	var->i++;
}

char	*var_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && ft_is_var_char(str[i]))
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

int	get_var_size(char *str, t_list *env)
{
	if (!str)
		return (1);
	if (!find_env_var(env, str))
		return (0);
	else
		return (ft_strlen(find_env_var(env, str)));
}

int	ft_is_var_char(int c)
{
	if (!(ft_isalpha(c)))
	{
		if (!(ft_isdigit(c)))
		{
			if (c != '_')
				return (0);
		}
	}
	return (1);
}
