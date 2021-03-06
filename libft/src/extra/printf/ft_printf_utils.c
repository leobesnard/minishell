/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:54:26 by lbesnard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/19 20:49:35 by rmorel           ###   ########.fr       */
=======
/*   Updated: 2022/07/11 13:58:32 by rmorel           ###   ########.fr       */
>>>>>>> 095dfecf715f171790e8ed71f2b219053c9da822
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

int	ft_strlen_prtf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
