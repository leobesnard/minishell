/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:09:20 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 16:10:25 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_var_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*find_before_equal(char *str)
{
	char	*equal;
	char	*before_equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	before_equal = ft_substr(str, 0, equal - str);
	if (!before_equal)
		return (NULL);
	return (before_equal);
}
