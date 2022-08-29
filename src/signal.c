/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:18 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 18:51:01 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	signal_management(int status)
{
	if (status == NORMAL)
	{
		termios_management(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_normal);
	}
	if (status == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sigint_child);
	}
	return (0);
}

int	termios_management(bool echo_ctl)
{
	struct termios	termios_struct;
	int				ret_status;

	ret_status = tcgetattr(STDOUT_FILENO, &termios_struct);
	if (ret_status == -1)
		return (-1);
	if (echo_ctl)
		termios_struct.c_lflag |= ECHOCTL;
	else
		termios_struct.c_lflag &= ~(ECHOCTL);
	ret_status = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_struct);
	if (ret_status == -1)
		return (-1);
	return (0);
}

void	sigint_normal(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_child(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
