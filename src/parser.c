/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:26 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/21 20:16:22 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	tok_error(char *str)
{
	printf("bash: syntax error near unexpected token `%s'\n", str);
	g_minishell.last_exec_code = 2;
	return (SYNTAX_ERROR);
}

static int	is_redirector(char *s)
{
	if (s[0] && (s[0] == '>' || s[0] == '<'))
		return (1);
	return (0);
}

int	check_pipe_slash(t_list *list)
{
	char	*s;

	s = ((t_token *)list->content)->word;
	if (((t_token *)list->content)->type == PIPE)
		return (tok_error(((t_token *)list->content)->word));
	if (s[0] == '/' && !s[1])
	{
		printf("bash: %s: Is a directory\n", ((t_token *)list->content)->word);
		g_minishell.last_exec_code = 126;
		return (SYNTAX_ERROR);
	}
	return (0);
}

int	check_syntax(t_list *list)
{
	if (check_pipe_slash(list) != 0)
		return (SYNTAX_ERROR);
	while (list)
	{
		if (is_redirector(((t_token *)list->content)->word))
		{
			if (!list->next)
				return (tok_error("newline"));
			if (is_redirector(((t_token *)list->next->content)->word)
				|| ((t_token *)list->next->content)->type == PIPE)
				return (tok_error(((t_token *)list->next->content)->word));
		}
		else if (((t_token *)list->content)->type == PIPE)
		{
			if (!list->next)
				return (tok_error("newline"));
			if (((t_token *)list->next->content)->type == PIPE)
				return (tok_error(((t_token *)list->next->content)->word));
		}
		list = list->next;
	}
	return (0);
}

int	parser(t_list *list, t_list **parsed)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = NULL;
	cmd = NULL;
	(void)parsed;
	if (check_syntax(list) == SYNTAX_ERROR) //|| check_all_quotes(list))
		return (SYNTAX_ERROR);
	while (list)
	{
		if (empty_cmd(&cmd) == MEM_ERROR)
			return (exit_cmd(parsed, MEM_ERROR, 0, cmd));
		if (fill_cmd(&list, cmd) == MEM_ERROR)
			return (exit_cmd(parsed, MEM_ERROR, 1, cmd));
		tmp = ft_lstnew(cmd);
		if (!tmp)
			return (exit_cmd(parsed, MEM_ERROR, 1, cmd));
		ft_lstadd_back(parsed, tmp);
	}
	return (0);
}
