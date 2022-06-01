/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:54:26 by lbesnard          #+#    #+#             */
/*   Updated: 2021/12/10 17:50:08 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_putchar(int c)
{
	write_buff(c, 0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
