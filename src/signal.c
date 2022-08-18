/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:18 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/18 20:58:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	signal_management(int status)
{
	if (status != CHILD)
		signal(SIGQUIT, SIG_IGN);
	if (status == NORMAL)
		signal(SIGINT, sigint_normal);
	if (status == CHILD)
		signal(SIGINT, sigint_child);
	return (0);
}

void	sigint_normal(int signum)
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
	rl_redisplay();
}

void	sigint_child(int signum)
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
}
