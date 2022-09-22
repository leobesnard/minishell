/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:57:51 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/22 14:50:56 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "libft.h"

//		free.c

void	free_token(void *token);
t_list	*free_token_list(t_list **list);
char	**free_ptr(char **ptr);
void	free_envdup(t_env *env);
void	free_array(char ***args);

//		free2.c

void	free_parsed(t_list **parsed);
int		free_env(t_env *env);
int		free_heredoc(t_env *env, t_cmd_fd *cmd_fd, char *str);
int		free_before_exit(t_env *env, char **argv,
			t_cmd_fd *cmd_fd, t_list **apsd);
int		free_lexer(t_list *lst);

#endif
