/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:36:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/08/22 18:44:55 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/* builtin.c */
t_list	*builtin_unset(t_list *env, char *str);
t_list	*builtin_export(t_list *env, char *str);
int		builtin_cd(t_list *env, char **args);
void	builtin_echo(char **str);
void	builtin_pwd(t_list *env);
void	builtin_env(t_list *env);
int		builtin_exit(t_list *parsed);
int		ft_atol(const char *nptr);

#endif
