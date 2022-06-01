/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:42:37 by lbesnard          #+#    #+#             */
/*   Updated: 2021/11/24 14:44:42 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			i;
	size_t			dest_len;
	size_t			src_len;
	int				n;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	n = 0;
	i = ft_strlen(dest);
	if (size <= dest_len)
		return (size + src_len);
	while (i < (size - 1) && src[n])
	{
		dest[i] = src[n];
		i++;
		n++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
