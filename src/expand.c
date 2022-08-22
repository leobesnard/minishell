/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:56:45 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/17 18:11:06 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_check_quotes(char *str)
{
	int	i;

	i = 0;
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

int test_size_expand(char *str, t_list *env)
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
			var_incr(&var);
			while (str[var.i] != '\'')
				var_incr(&var);
			var.sz -= 2;
		}
		if (str[var.i] == '$')
		{
			var.i++;
			var.str = var_str(&str[var.i]);
			while (str[var.i] && ft_is_var_char(str[var.i]))
				var.i++;
			var.sz += get_var_size(var.str, env);
			free(var.str);
			var.str = NULL;
		}
		if (str[var.i] == '\"')
		{
			var.i++;
			while (str[var.i] != '\"')
				var_incr(&var);
			var.i++;
		}
		if (str[var.i])
			var_incr(&var);
		printf("i = %d\n", var.i);
	}
	return (var.sz);
}

void	var_incr(t_var *var)
{
	var->sz++;
	var->i++;
}

char    *var_str(char *str)
{
    int        i;
    char    *ret;

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
	{
		printf("%ld", ft_strlen(find_env_var(env, str)));
		return (ft_strlen(find_env_var(env, str)));
	}
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
