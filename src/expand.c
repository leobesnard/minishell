/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:56:45 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 18:39:41 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_check_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (-1);
		}
		i++;
	}
	return (0);
}

int size_expand(char *str, t_list *env)
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
		{
			var.i++;
			while (str[var.i] && str[var.i] != '\'')
				var_incr(&var);
			var.i++;
		}
		else if (str[var.i] == '$')
		{
			if (str[var.i + 1] && ft_is_var_char(str[var.i + 1]))
			{
				var.i++;
				var.str = var_str(&str[var.i]);
				while (str[var.i] && ft_is_var_char(str[var.i]))
					var.i++;
				var.sz += get_var_size(var.str, env);
				free(var.str);
				var.str = NULL;
			}
			else
				var_incr(&var);
		}
		else if (str[var.i] == '\"')
		{
			var.i++;
			while (str[var.i] != '\"')
			{
				if (str[var.i] == '$')
				{
					if (str[var.i + 1] && ft_is_var_char(str[var.i + 1]))
					{
						var.i++;
						var.str = var_str(&str[var.i]);
						while (str[var.i] && ft_is_var_char(str[var.i]))
							var.i++;
						var.sz += get_var_size(var.str, env);
						free(var.str);
						var.str = NULL;
					}
					else
						var_incr(&var);
				}
				else
					var_incr(&var);
			}
			var.i++;
		}
		else
			var_incr(&var);
	}
	return (var.sz);
}

char	*expand(t_list *env, char *str)
{
	t_vars	var;

	if (test_check_quotes(str))
		return (NULL);
	var.ret = malloc(sizeof(char) * size_expand(str, env) + 1);
	if (!var.ret)
		return (NULL);
	var.i = 0;
	var.u = 0;
	while (str[var.i])
	{
		if (str[var.i] == '\'')
		{
			var.i++;
			while (str[var.i] && str[var.i] != '\'')
			{
				var.ret[var.u] = str[var.i];
				var.i++;
				var.u++;
			}
			var.i++;
		}
		else if (str[var.i] == '\"')
		{
			var.i++;
			while (str[var.i] && str[var.i] != '\"')
			{
				if (str[var.i] == '$')
				{
					if (str[var.i + 1] && ft_is_var_char(str[var.i + 1]))
					{
						var.i++;
						var.str = var_str(&str[var.i]);
						var.var = find_env_var(env, var.str);
						if (var.var)
							ft_strlcpy(&var.ret[var.u], var.var, ft_strlen(var.var) + 1);
						while (ft_is_var_char(str[var.i]))
							var.i++;
						free(var.str);
						if (var.var)
							var.u += ft_strlen(var.var);
					}
					else
					{
						var.ret[var.u] = str[var.i];
						var.u++;
						var.i++;
					}
				}
				else
				{
					var.ret[var.u] = str[var.i];
					var.u++;
					var.i++;
				}
			}
			var.i++;
		}
		else if (str[var.i] == '$')
		{
			if (str[var.i + 1] && ft_is_var_char(str[var.i + 1]))
			{
				var.i++;
				var.str = var_str(&str[var.i]);
				var.var = find_env_var(env, var.str);
				if (var.var)
					ft_strlcpy(&var.ret[var.u], var.var, ft_strlen(var.var) + 1);
				while (ft_is_var_char(str[var.i]))
					var.i++;
				free(var.str);
				if (var.var)
					var.u += ft_strlen(var.var);
			}
			else
			{
				var.ret[var.u] = str[var.i];
				var.u++;
				var.i++;
			}
		}
		else
		{	
			var.ret[var.u] = str[var.i];
			var.u++;
			var.i++;
		}
	}
	free(str);
	var.ret[var.u] = '\0';
	return (var.ret);
}
