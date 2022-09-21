/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:26:30 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 18:21:21 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_expand(t_vars *var, char *str, t_list *env)
{
	var->ret = malloc(sizeof(char) * size_expand(str, env) + 1);
	if (!var->ret)
		return (-1);
	var->i = 0;
	var->u = 0;
	return (0);
}

void	expand_simple_quotes(char *str, t_vars *var)
{
	var->i++;
	while (str[var->i] && str[var->i] != '\'')
		incr(str, var);
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
		incr(str, var);
}

void	expand_double_quotes(t_vars *var, t_list *env, char *str)
{
	var->i++;
	while (str[var->i] && str[var->i] != '\"')
	{
		if (str[var->i] == '$')
			expand_dollar(var, env, str);
		else
			incr(str, var);
	}
	var->i++;
}
