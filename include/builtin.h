/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:36:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/04 17:10:28 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/* builtin.c */
t_list	*unset(t_list *env, char *str);
void	echo(char **str);
void	pwd(t_list *env);
void	env(t_list *env);

#endif
