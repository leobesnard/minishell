/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:47 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/22 23:10:22 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "minishell.h"

/* env.c */
char	*find_env_var(char **env, char *var);
char	**add_var(char **env, char *var);
t_list	*dup_env(char **envp);
#endif