/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:49:55 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 20:15:25 by lbesnard         ###   ########.fr       */
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
	return (del_var(env, str));
}

t_list	*builtin_export(t_list *env, char *str)
{
	if (!ft_strchr(str, '='))
		return (env);
	if (find_env_var(env, str))
		env = builtin_unset(env, str);
	add_var(env, str);
	return (env);
}
