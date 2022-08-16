/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:18 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/15 21:10:53 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	signal_management(int status)
{
	if (status != CHILD)
		signal(SIGQUIT, SIG_IGN);
	if (status == CHILD)
		signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handler);
	return (0);
}

void	handler(int signum)
{
	t_process	*proc;

	(void)signum;
	while (g_minishell.process)
	{
		printf("handle_sigint loop\n");
		proc = (t_process *)g_minishell.process->content;
		if (kill(proc->pid, 0) > 0)
			kill(proc->pid, SIGINT);
		g_minishell.process = g_minishell.process->next;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_minishell.status != CHILD)
		rl_redisplay();
}
