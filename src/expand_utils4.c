/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:34:45 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/28 16:07:22 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sizeof_simple_quote(t_var *var, char *str)
{
	var_incr(var);
	while (str[var->i] && str[var->i] != '\'')
		var_incr(var);
	var_incr(var);
}

void	to_next_simple_quote(char *str, t_vars *var)
{
	incr(str, var);
	while (str[var->i] && str[var->i] != '\'')
		incr(str, var);
	incr(str, var);
}

int	size_first_expand(char *str, t_list *env)
{
	t_var	var;

	var.i = 0;
	var.sz = 0;
	var.str = NULL;
	if (test_check_quotes(str))
		return (-1);
	while (str[var.i])
	{
		if (str[var.i] == '\'')
			sizeof_simple_quote(&var, str);
		else if (str[var.i] == '$')
			dollar_size(&var, str, env);
		else
			var_incr(&var);
	}
	return (var.sz);
}

int	init_first_expand(t_vars *var, char *str, t_list *env)
{
	var->ret = malloc(sizeof(char) * size_first_expand(str, env) + 1);
	if (!var->ret)
		return (-1);
	var->i = 0;
	var->u = 0;
	return (0);
}

char	*expand_before(t_list *env, char *str, int *flag)
{
	t_vars	var;

	if (!str)
		return (NULL);
	if (test_check_quotes(str))
	{
		*flag = 1;
		return (NULL);
	}
	if (init_first_expand(&var, str, env))
		return (NULL);
	while (str[var.i])
	{
		if (str[var.i] == '\'')
			to_next_simple_quote(str, &var);
		else if (str[var.i] == '$')
			expand_dollar(&var, env, str);
		else
			incr(str, &var);
	}
	free(str);
	var.ret[var.u] = '\0';
	return (var.ret);
}
