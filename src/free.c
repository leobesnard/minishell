/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:45:38 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 20:15:52 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	t_token	*tok;

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
	//free(env->command_buf);
	free_envdup(env); 
	return (0);
}

int	free_before_exit(t_env *env, char **argv, t_cmd_fd *cmd_fd, t_list **apsd)
{
	free_parsed(&env->parsed);
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
