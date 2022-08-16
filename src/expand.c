/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:31:58 by lbesnard          #+#    #+#             */
/*   Updated: 2022/08/16 15:33:42 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*outside_quote(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != '\"' && str[i] != $ && str[i] != '\'' && str[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i);
	return (ret);
}

char	*expand(char *str)
{
	 char	*ret;
	 int	i;

	i = 0;
	ret = malloc(sizeof(char) * (strlen(str) + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39)
		{
			
		}
		i++;
	}
}
