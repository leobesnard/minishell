/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:56:45 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/22 14:45:45 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty(t_list *lexer)
{
	t_list	*tmp;
	t_list	*lst;

	lst = lexer;
	while (lst && lst->next)
	{
		tmp = lst->next;
		if (!(*((t_token *)tmp->content)->word))
		{
			lst->next = tmp->next;
			ft_lstdelone(tmp, &free_token);
		}
		lst = lst->next;
	}
}

int	simple_double_quotes(char *str, int i)
{
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
			{
				i++;
			}
			if (!str[i])
				return (-1);
		}
		i++;
	}
	return (0);
}

int	test_check_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (simple_double_quotes(str, i))
		return (-1);
	return (0);
}

int	size_expand(char *str, t_list *env)
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
			simple_quote_size(&var, str);
		else if (str[var.i] == '$')
			dollar_size(&var, str, env);
		else if (str[var.i] == '\"')
			double_quote_size(&var, str, env);
		else
			var_incr(&var);
	}
	return (var.sz);
}

char	*expand(t_list *env, char *str, int *flag)
{
	t_vars	var;

	if (!str)
		return (NULL);
	if (test_check_quotes(str))
	{
		*flag = 1;
		return (NULL);
	}
	if (init_expand(&var, str, env))
		return (NULL);
	while (str[var.i])
	{
		if (str[var.i] == '\'')
			expand_simple_quotes(str, &var);
		else if (str[var.i] == '\"')
			expand_double_quotes(&var, env, str);
		else if (str[var.i] == '$')
			expand_dollar(&var, env, str);
		else
			incr(str, &var);
	}
	free(str);
	var.ret[var.u] = '\0';
	return (var.ret);
}
