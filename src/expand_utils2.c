/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:26:30 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/01 17:38:12 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_incr(t_vars *var, char *str)
{
	var->ret[var->u] = str[var->i];
	var->u++;
	var->i++;
}

void	expand_single_quote(t_vars *var, char *str)
{
	var->i++;
	while (str[var->i] && str[var->i] != '\'')
	{
		var->ret[var->u] = str[var->i];
		var->i++;
		var->u++;
	}
	var->i++;
}

void	expand_dollar(t_vars *var, t_list *env, char *str)
{
	if (str[var->i + 1] && ft_is_var_char(str[var->i + 1]))
	{
		var->i++;
		var->str = var_str(&str[var->i]);
		var->var = find_env_var(env, var->str);
		if (var->var)
			ft_strlcpy(&var->ret[var->u], var->var, ft_strlen(var->var) + 1);
		while (ft_is_var_char(str[var->i]))
			var->i++;
		free(var->str);
		if (var->var)
			var->u += ft_strlen(var->var);
	}
	else
		cpy_incr(var, str);
}
