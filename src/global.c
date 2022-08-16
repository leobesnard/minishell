/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:34:23 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/15 16:08:23 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	add_process_to_global(void)
{
	t_list		*proc;
	t_process	*proc_id;

	proc_id = malloc(sizeof(t_process));
	if (!proc_id)
		return (MEM_ERROR);
	proc_id->pid = getpid();
	proc_id->status = 1;
	proc = ft_lstnew(proc_id);
	if (!proc)
		return (MEM_ERROR);
	ft_lstadd_back(&g_minishell.process, proc);
	return (0);
}

void	finish_job_status(void)
{
	while (g_minishell.process)
	{
		if (kill(((t_process *)g_minishell.process->content)->pid, 0) <= 0)
		{
			((t_process *)g_minishell.process->content)->pid = 0;
		}
		g_minishell.process = g_minishell.process->next;
	}
	return ;
}
