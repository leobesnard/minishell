/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:38:54 by lbesnard          #+#    #+#             */
/*   Updated: 2022/08/12 18:53:49 by lbesnard         ###   ########.fr       */
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

int	builtin_exit(t_list *parsed)
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
			return (ft_putstr_fd("exit: numeric argument required", 2),
			exit(2), 2);
		word = ((t_token *)args->next->content)->word;
	}
	if (word)
		return (ft_putstr_fd("exit: too many arguments", 2), 1);
	exit(g_minishell.last_exec_code);
}
