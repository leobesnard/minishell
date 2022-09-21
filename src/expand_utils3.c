/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:29:29 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 19:03:39 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_size(t_var *var, char *str, t_list *env)
{
	if (str[var->i + 1] && ft_is_var_char(str[var->i + 1]))
	{
		var->i++;
		var->str = var_str(&str[var->i]);
		while (str[var->i] && ft_is_var_char(str[var->i]))
			var->i++;
		var->sz += get_var_size(var->str, env);
		free(var->str);
		var->str = NULL;
	}
	else
		var_incr(var);
}

void	simple_quote_size(t_var *var, char *str)
{
	var->i++;
	while (str[var->i] && str[var->i] != '\'')
		var_incr(var);
	var->i++;
}

void	double_quote_size(t_var *var, char *str, t_list *env)
{
	var->i++;
	while (str[var->i] != '\"')
	{
		if (str[var->i] == '$')
			dollar_size(var, str, env);
		else
			var_incr(var);
	}
	var->i++;
}
