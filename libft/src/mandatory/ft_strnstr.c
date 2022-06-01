/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:54:18 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 12:32:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	if (ft_strlen(little) < len)
		n = ft_strlen(little);
	else
		n = len;
	if (len == 0)
		return (0);
	if (ft_strlen(little) == 0)
		return ((char *)&big[i]);
	while (big[i] && i <= (len - ft_strlen(little)))
	{
		if (!(ft_strncmp(&big[i], &little[0], ft_strlen(little))))
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
