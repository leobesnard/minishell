/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:54:48 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 17:28:21 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

static int	ft_wrdcnt(char const*str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			word++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (word);
}

static char	*ft_getwrd(char const *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[len] != c && str[len])
		len++;
	word = malloc(sizeof(*str) * (len + 1));
	if (!word)
		return (0);
	while (str[i] != c && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **tab, int x)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		free(tab[i]);
		i++;
	}
	return (0);
}

static char	**ft_fill(char **tab, char *str, int x, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			tab[x] = ft_getwrd(&str[i], c);
			if (!tab[x])
				return (ft_free(tab, x));
			x++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	tab[ft_wrdcnt(str, c)] = 0;
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**tab;
	int		x;

	i = 0;
	x = 0;
	if (!str)
		return (0);
	tab = malloc(sizeof(*tab) * (ft_wrdcnt(str, c) + 1));
	if (!(tab))
		return (0);
	tab = ft_fill(tab, (char *)str, x, c);
	return (tab);
}
