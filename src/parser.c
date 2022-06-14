/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:50:48 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/14 18:00:43 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_cmd_list(t_list *list)
{
	t_list			*cmd_lst;
	t_cmd			*cmd;
	t_token			*token;

	if (!list)
		return (NULL);
	cmd_lst = NULL;
	token = (t_token *)list->content;
	while (list)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		ft_bzero(cmd, sizeof(t_cmd));
		if (fill_cmd(cmd, list) == -1)
			return (NULL);
		printf("mdr je suis nul\n");
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		while (list && token->type != PIPE)
		{
			list = list->next;
			if (list)
				token = (t_token *)list->content;
		}
		if (list)
			list = list->next;
		if (list)
			token = (t_token *)list->content;
	}
	return (cmd_lst);
}

char	**malloc_cmd_arg(t_list *list)
{
	char 	**arg;
	t_token	*token;
	t_list	*tmp;
	int		i;

	tmp = list;
	token = (t_token *)tmp->content;
	i = 1;
	while (tmp && token->type == WORD)
	{
		tmp = tmp->next;
		printf("Token : [%d] | %s\n", i, token->word);
		if (tmp)
			token = (t_token *)tmp->content;
		i++;
	}
	printf("Final i = %d\n", i);
	arg = malloc(sizeof(char *) * i);
	if (!arg)
		return (NULL);
	arg[i - 1] = NULL;
	return (arg);
}

int	fill_cmd_arg(t_cmd *cmd, t_list **alist)
{
	int			i;
	t_token		*token;
	t_list		*list;

	i = 0;
	list = *alist;
	token = (t_token *)list->content;
	cmd->arg = malloc_cmd_arg(list);
	if (!cmd->arg)
		return (-1);
	while (list && token->type == WORD)
	{
		cmd->arg[i] = ft_strdup(token->word);
		printf("cmd->arg[%d] = %s\n", i, cmd->arg[i]);
		if (!cmd->arg[i])
			return (-1);
		list = list->next;
		if (list)
			token = (t_token *)list->content;
		i++;
	}
	printf("end\n");
	cmd->nb_arg = i;
	*alist = list;
	return (0);
}

int	last_word(t_list *list)
{
	t_token	*token;
	t_list	*tmp;
	int		i;

	tmp = list;
	token = (t_token *)tmp->content;
	i = 0;
	while (tmp && token->type == WORD)
	{
		tmp = tmp->next;
		if (tmp)
			token = (t_token *)tmp->content;
		i++;
	}
	return (i);
}

int	fill_cmd_rd(t_cmd *cmd, t_list **alist)
{
	int				i;
	t_token			*token;
	t_list			*list;
	t_token_type	tmp_token_rd;

	list = *alist;
	token = (t_token *)list->content;
	tmp_token_rd = 0;
	if (!*alist)
		return (-1);
	tmp_token_rd = token->type;
	list = list->next;
	token = (t_token *)list->content;
	if (!list || token->type != WORD)
		return (-1);
	i = last_word(list);
	while (--i > 0)
		list = list->next;
	if (tmp_token_rd == 5 || tmp_token_rd == 7)
		cmd->outfile = ft_strdup(token->word);
	if (tmp_token_rd == 7)
		cmd->append_outfile = 1;
	else if (tmp_token_rd == 6)
		cmd->infile = ft_strdup(token->word);
	list = list->next;
	*alist = list;
	return (0);
}

int	fill_cmd(t_cmd *cmd, t_list *list)
{
	t_token			*token;

	token = (t_token *)list->content;
	while (list && token->type != PIPE)
	{
		if (fill_cmd_arg(cmd, &list) == -1)
			return (-1);
		while (list && (token->type >= 1 && token->type <= 4))
		{
			if (fill_cmd_rd(cmd, &list) == -1)
				return (-1);
		}
	}
	return (0);
}
