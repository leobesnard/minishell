/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:49:55 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/04 17:10:53 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str)
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

void	pwd(t_list *env)
{
	printf("%s\n", find_env_var(env, "PWD"));
}

void	env(t_list *env)
{
	while(env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

t_list	*unset(t_list *env, char *str)
{
	return (del_var(env, str));
}
