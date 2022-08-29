/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:33:34 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/19 20:12:35 by bek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

int		signal_management(int status);
int		termios_management(bool echo_ctl);
void	sigint_normal(int signum);
void	sigint_child(int signum);

#endif
