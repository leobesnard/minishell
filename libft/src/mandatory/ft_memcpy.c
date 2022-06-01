/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:40:39 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 12:32:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptos;
	char	*ptod;
	size_t	i;

	ptos = (char *)src;
	ptod = (char *)dest;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (i < n)
	{
		ptod[i] = ptos[i];
		i++;
	}
	return (ptod);
}
