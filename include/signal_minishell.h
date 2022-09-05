/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:33:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/01 14:55:23 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

int		signal_management(int status);
int		termios_management(bool echo_ctl);
void	sigint_normal(int signum);
void	sigint_child(int signum);
void	sigint_heredoc(int signum);

#endif
