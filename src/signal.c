/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:18 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/07 22:40:25 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_management(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) != 0)
		printf("Erreur de signal SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		ft_printf("Erreur de signal SIGQUIT");
	return (0);
}

void	handler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	if (signo == SIGINT)
	{

	}
	else if (signo == SIGQUIT)
	{

	}
	else if (signo == 
}
