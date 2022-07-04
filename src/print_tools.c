/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:22:10 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 17:56:09 by rmorel           ###   ########.fr       */
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

void	print_cmd_fd(t_cmd_fd *cmd_fd, char *str)
{
	printf("%s: STDIN[%d]-STDOU[%d]-fd[0][%d]-fd[1][%d]-tmp[%d]\n", str,
			STDIN_FILENO, STDOUT_FILENO, cmd_fd->fd[0], cmd_fd->fd[1],
			cmd_fd->tmp);
}	
