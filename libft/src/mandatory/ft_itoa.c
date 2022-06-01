/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 00:24:13 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 12:32:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_createstr(int n)
{
	int		i;
	char	*str;

	i = 0;
	if (n == 0)
	{
		str = malloc(sizeof(*str) * 2);
		if (!str)
			return (0);
		str[1] = '\0';
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	str = malloc(sizeof(*str) * i + 1);
	if (!str)
		return (0);
	str[i] = '\0';
	return (str);
}

static int	ft_getsize(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_putinstr(char *str, int n, int index)
{
	char	c;

	c = n + 48;
	str[index] = c;
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			size;
	long int	nbr;

	nbr = n;
	if (nbr == 0)
		return (ft_createstr(nbr));
	str = ft_createstr(nbr);
	if (!str)
		return (0);
	size = ft_getsize(nbr);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr != 0)
	{
		size--;
		ft_putinstr(str, (nbr % 10), size);
		nbr /= 10;
	}
	return (str);
}
