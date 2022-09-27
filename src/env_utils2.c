/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:32:00 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 21:22:33 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		n;

	i = 0;
	n = ft_strlen(s1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((const char)s1[i] - (const char)s2[i]);
}

void	to_next_node(t_list **tmp, t_list **node, char *str)
{
	*tmp = *node;
	*node = (*node)->next;
	free(str);
}

void	free_node_and_equal(t_list *node, char *str)
{
	free(str);
	free(node->content);
	free(node);
}

int	bigger_str(char *str1, char *str2)
{
	int	ret;
	int	size1;
	int	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 > size2)
		ret = size1;
	else
		ret = size2;
	return (ret);
}
