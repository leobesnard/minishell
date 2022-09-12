/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:49:55 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/12 12:54:54 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	/*if (!str[1])
		return (ft_printf("\n"), 1);
	tiret_n = check_tiret_n(str[1]);
	if (!tiret_n)
		i = 1;
	else
		i = 2;*/
	while (str[i])
	{
		printf("%s", str[i]	);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!tiret_n)
		printf("\n");
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
	while(env)
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
