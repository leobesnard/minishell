/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:18 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/19 18:00:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	signal_management(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) != 0)
		printf("Erreur de signal SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		printf("Erreur de signal SIGQUIT");
	return (0);
}

void	handler(int signo, siginfo_t *info, void *context)
{
	t_process	*proc;

	(void)context;
	(void)info;
	if (signo == SIGINT)
	{
		while (g_minishell.process)
		{
			proc = (t_process *)g_minishell.process->content;
			if (kill(proc->pid, 0) > 0)
				kill(proc->pid, SIGINT);
			g_minishell.process = g_minishell.process->next;
		}
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		if (g_minishell.status != EXEC_STATUS)
			rl_redisplay();
	}
}
