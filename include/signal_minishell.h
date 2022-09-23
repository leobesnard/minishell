/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:33:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/23 14:49:19 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MINISHELL_H
# define SIGNAL_MINISHELL_H

int		signal_management(int status);
int		termios_management(bool echo_ctl);
void	sigint_normal(int signum);
void	sigint_child(int signum);
void	sigint_heredoc(int signum);

#endif
