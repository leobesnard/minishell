/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:43:08 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 16:07:30 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(const char *set, int c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		i;
	int		n;

	i = 0;
	if (!s1 || !set)
		return (0);
	n = ft_strlen(s1);
	while (ft_is_in_set(set, s1[i]))
		i++;
	if (n <= i)
	{
		p = malloc(sizeof(*s1) * 1);
		p[0] = '\0';
		return (p);
	}
	while (ft_is_in_set(set, s1[n - 1]))
		n--;
	p = malloc(sizeof(*s1) * (n - i + 1));
	if (!p)
		return (0);
	ft_strlcpy(p, &s1[i], (n - i + 1));
	return (p);
}
