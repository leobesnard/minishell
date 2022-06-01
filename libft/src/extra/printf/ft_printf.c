/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:57:54 by lbesnard          #+#    #+#             */
/*   Updated: 2021/12/13 15:07:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	write_buff(int c, int marker)
{
	static int	buflen = 0;
	static char	buffer[42];
	static int	ret = 0;

	if (buflen == 42)
	{
		write(1, &buffer, buflen);
		ret += buflen;
		buflen = 0;
	}
	if (marker)
	{
		write(1, &buffer, buflen);
		ret += buflen;
		buflen = 0;
		return (ret);
	}
	buffer[buflen] = c;
	buflen++;
	return (1);
}

static int	ft_parser(va_list args, char type)
{
	if (type == 'c')
		ft_putchar(va_arg(args, int));
	if (type == 's')
		ft_putstr(va_arg(args, char *));
	if (type == 'p')
		ft_putadrss(va_arg(args, unsigned long));
	if (type == 'd')
		ft_putnbr(va_arg(args, int));
	if (type == 'i')
		ft_putnbr(va_arg(args, int));
	if (type == 'u')
		ft_putunbr(va_arg(args, unsigned int));
	if (type == 'x')
		ft_putnbr_base(va_arg(args, int), "0123456789abcdef");
	if (type == 'X')
		ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF");
	if (type == '%')
		ft_putchar('%');
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;
	int		spe;

	i = 0;
	spe = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			ft_parser(args, format[i + 1]);
			i++;
		}
		else
			write_buff(format[i], 0);
		i++;
	}
	ret = write_buff('\0', 1);
	va_end(args);
	return (ret);
}
