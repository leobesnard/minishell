/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:56:16 by lbesnard          #+#    #+#             */
/*   Updated: 2022/08/16 12:04:41 by rmorel           ###   ########.fr       */
/*   Updated: 2022/07/11 13:58:19 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

void	ft_putchar(int c);
void	ft_putnbr(int nb);
void	ft_putunbr(int nb);
int		ft_strlen_prtf(char *str);
void	ft_putstr(char *str);
int		write_buff(int c, int marker);
void	ft_putadrss(unsigned long ptr);
int		ft_printf(const char *format, ...);
void	ft_putnbr_base(int nb, char *base);

#endif
