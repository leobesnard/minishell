/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:22:10 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/27 12:47:44 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_list *list)
{
	t_list	*cmd_arg;
	t_list	*cmd_rd;
	int		i;

	i = 0;
	while (list)
	{
		printf("-------------- cmd[%d] --------------\n", i++);
		cmd_arg = ((t_cmd *)list->content)->arg;
		cmd_rd = ((t_cmd *)list->content)->rd;
		print_token_list(cmd_arg, "arg");
		print_token_list(cmd_rd, "rd");
		list = list->next;
	}
}

void	print_token_list(t_list *list, char *str)
{
	int	j;

	j = 0;
	while (list)
	{
		printf("%s[%d] : %s\n", str, j++, ((t_token *)list->content)->word);
		list = list->next;
	}
}

void	print_tab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s[%d] = %s\n", str, i, tab[i]);
		i++;
	}
}
