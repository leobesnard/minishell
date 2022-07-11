/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:49:55 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/11 14:43:52 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **str)
{
	int	i;

	if (ft_strncmp(str[0], "-n", 3))
		i = 0;
	else
		i = 1;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(str[0], "-n", 3))
		printf("\n");
}

void	builtin_pwd(t_list *env)
{
	char	*ret;
	
	ret = find_env_var(env, "PWD");
	if (ret)
		printf("%s\n", find_env_var(env, "PWD"));
	return ;
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
	env = add_var(env, str);
	return (env);
}
