/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:47 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/15 22:15:47 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "minishell.h"

/* env.c */
char	*find_env_var(t_list *env, char *var);
t_list	*del_var(t_list *env, char *var);
int		add_var(t_list *env, char *var);
t_list	*dup_env(char **envp);

/* env_utils.c */
int		strcmp(const char *s1, const char *s2);
char	*get_var(char *env_i);
int		is_alpha_spe(int c);

#endif