/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:38:54 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/12 17:04:56 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

int	is_arg_numeric(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_list *parsed, t_env *env)
{
	t_list	*args;
	char	*word;

	args = ((t_cmd *)parsed->content)->arg->next;
	if (args)
		word = ((t_token *)args->content)->word;
	else 
		word = NULL;
	printf("exit\n");
	if (word)
	{
		if (!is_arg_numeric(word))
			return (ft_putstr_fd("exit: numeric argument required\n", 2),
			exit(2), 2);
	}
	if (args && args->next)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	if (!args)
	{
		free_before_quit(env);
		exit(g_minishell.last_exec_code);
	}
	else
	{
		free_before_quit(env);
		exit((unsigned int)ft_atol(word));
	}
	return (0);
}
