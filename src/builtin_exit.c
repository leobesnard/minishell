/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:38:54 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 16:34:15 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

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

int	builtin_exit(t_list *parsed, t_env *env, char **argv, t_cmd_fd *cmd_fd)
{
	t_list			*args;
	char			*word;

	if (parsed)
		args = ((t_cmd *)parsed->content)->arg->next;
	else
		args = NULL;
	if (args)
		word = ((t_token *)args->content)->word;
	else
		word = NULL;
	printf("exit\n");
	env->cmd_fd = cmd_fd;
	return (exit_1(env, argv, word, args));
}
