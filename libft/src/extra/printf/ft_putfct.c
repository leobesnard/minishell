/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:34:13 by lbesnard          #+#    #+#             */
/*   Updated: 2021/12/10 17:49:26 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb)
{
	long int	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_putunbr(int nb)
{
	unsigned int	n;

	n = nb;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_putnbr_base(int nb, char *base)
{
	unsigned int	n;

	n = nb;
	if (n > (ft_strlen(base) - 1))
	{
		ft_putnbr_base(n / ft_strlen(base), base);
		ft_putnbr_base(n % ft_strlen(base), base);
	}
	else
		ft_putchar(base[n]);
}

void	ft_putnbr_hex_base(unsigned long nb, char *base)
{
	unsigned long	n;

	n = nb;
	if (n > (ft_strlen(base) - 1))
	{
		ft_putnbr_hex_base(n / ft_strlen(base), base);
		ft_putnbr_hex_base(n % ft_strlen(base), base);
	}
	else
		ft_putchar(base[n]);
}

void	ft_putadrss(unsigned long ptr)
{
	unsigned long	value;

	value = ptr;
	ft_putchar('0');
	ft_putchar('x');
	ft_putnbr_hex_base(value, "0123456789abcdef");
}
