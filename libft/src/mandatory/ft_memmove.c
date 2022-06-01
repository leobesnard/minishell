/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:08:13 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/30 12:32:58 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptos;
	char	*ptod;
	size_t	i;

	i = 0;
	ptos = (char *)src;
	ptod = (char *)dest;
	if (dest == NULL && src == NULL)
		return (0);
	if (src < dest)
	{
		while (n-- > 0)
			ptod[n] = ptos[n];
		return (dest);
	}
	while (i < n)
	{
		ptod[i] = ptos[i];
		i++;
	}
	return (dest);
}
