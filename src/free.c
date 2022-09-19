/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:45:38 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/19 08:44:37 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	t_token *tok;

	tok = token;
	free(tok->word);
	tok->word = NULL;
	free(tok);
	tok = NULL;
}

int	free_lexer(t_list *lst)
{
	ft_lstclear(&lst, &free_token);
	return (0);
}

int	free_env(t_env *env)
{
	free(env->command_buf);
	free_envdup(env); 
	return (0);
}

int	free_before_exit(t_env *env, char **argv,  t_cmd_fd *cmd_fd, t_list **apsd)
{
	free_parsed(apsd);
	free_env(env);
	free(argv);
	free(cmd_fd);
	return (0);
}

int	free_heredoc(t_env *env, t_cmd_fd *cmd_fd, char *str)
{
	free_parsed(&(env->parsed));
	free_env(env);
	free(cmd_fd);
	free(str);
	return (0);
}

t_list *free_token_list(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (list)
	{
		if (((t_token *)tmp->content)->word)
			free(((t_token *)tmp->content)->word);
		free(tmp->content);
		tmp = tmp->next;
	}
	*list = tmp;
	return (NULL);
}

char	**free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

void	free_envdup(t_env *env)
{
	t_list	*tmp;

	while (env->envdup)
	{
		tmp = env->envdup;
		env->envdup = env->envdup->next;
		free(tmp->content);
		free(tmp);
	}
	free(env);
}

void	free_node(t_list *node)
{
	free(node);
}

void	free_array(char ***args)
{
	int	i;

	i = 0;
	if (!(*args))
		return ;
	while ((*args)[i])
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
	return ;
}

void	free_parsed(t_list **parsed)
{
	t_list	*tmp;

	tmp = *parsed;
	while (tmp)
	{
		ft_lstclear(&((t_cmd *)tmp->content)->arg, &free_token);
		ft_lstclear(&((t_cmd *)tmp->content)->rd, &free_token);
		tmp = tmp->next;
	}
	ft_lstclear(parsed, free);
	*parsed = NULL;
}
