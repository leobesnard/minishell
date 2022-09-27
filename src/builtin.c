/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:49:55 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 22:29:03 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	builtin_echo(char **str)
{
	int	i;
	int	tiret_n;

	i = 1;
	tiret_n = 0;
	while (check_tiret_n(str[i]))
	{
		tiret_n = 1;
		i++;
	}
	while (str[i])
	{
		if (!ft_strncmp(str[i], "$?", 2))
			dollar_interro(str, i);
		else
		{
			ft_printf("%s", str[i]);
			if (str[i + 1])
				ft_printf(" ");
		}
		i++;
	}
	if (!tiret_n)
		ft_printf("\n");
	return (0);
}

void	builtin_pwd(t_list *env)
{
	char	*buf;

	buf = getcwd(0, 0);
	if (!buf)
		return ;
	printf("%s\n", buf);
	free(buf);
	(void)env;
}

void	builtin_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

t_list	*builtin_unset(t_list *env, char *str)
{
	if (!str)
		return (env);
	if (!is_var(str))
		return (ft_printf("'%s': not a valid identifier\n", str), env);
	return (del_var(env, str));
}

t_list	*builtin_export(t_list *env, char *str)
{
	char	*before_equal;

	if (!str)
		return (env);
	if (ft_isdigit(str[0]))
		return (ft_printf("'%s' : not a valid identifier\n", str), env);
	if (!ft_strchr(str, '='))
		return (env);
	before_equal = find_before_equal(str);
	if (find_env_var(env, before_equal))
	{
		env = builtin_unset(env, before_equal);
	}
	free(before_equal);
	add_var(&env, str);
	return (env);
}
