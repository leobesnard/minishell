/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:33:45 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 12:32:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptos;
	char	*p;

	ptos = (char *)str;
	if (str == 0)
		return (0);
	if (start > ft_strlen(str))
	{
		p = malloc(1);
		p[0] = '\0';
		return (p);
	}
	if (ft_strlen(&str[start]) < len)
		p = malloc(sizeof(*str) * (ft_strlen(&str[start]) + 1));
	else
		p = malloc(sizeof(*str) * (len + 1));
	if (p == NULL)
		return (0);
	if (start > ft_strlen(str))
		return (p);
	ft_strlcpy(p, &ptos[start], (len + 1));
	return (p);
}
