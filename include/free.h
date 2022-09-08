/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:57:51 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/08 19:01:25 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "libft.h"

/* free */
t_list	*free_token_list(t_list **list);
char	**free_ptr(char **ptr);
void	free_env(t_env *env);
void	free_array(char ***args);
void	free_parsed(t_list **parsed);
void	free_before_quit(t_env *env);
int		free_lexer(t_list *lst);

#endif
