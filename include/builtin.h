/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:36:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/12 17:09:05 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/* builtin.c */
t_list	*builtin_unset(t_list *env, char *str);
t_list	*builtin_export(t_list *env, char *str);
int		builtin_cd(t_list *env, char **args);
int		builtin_echo(char **str);
void	builtin_pwd(t_list *env);
void	builtin_env(t_list *env);
int		builtin_exit(t_list *parsed, t_env *env);

/* builtin_utils.c*/
int		ft_atol(const char *nptr);
int		check_tiret_n(char *str);

#endif
