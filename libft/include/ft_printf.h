/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:56:16 by lbesnard          #+#    #+#             */
/*   Updated: 2021/12/10 17:49:57 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_putchar(int c);
void	ft_putnbr(int nb);
void	ft_putunbr(int nb);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		write_buff(int c, int marker);
void	ft_putadrss(unsigned long ptr);
int		ft_printf(const char *format, ...);
void	ft_putnbr_base(int nb, char *base);

#endif