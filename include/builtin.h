/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:36:34 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/27 21:32:29 by lbesnard         ###   ########.fr       */
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
int		builtin_exit(t_list *parsed, t_env *env, char **argv, t_cmd_fd *cmd_fd);

/*builtin2.c*/
int		change_pwd(t_list *env, char *path, char *oldpath);

/*builtin_exit.c*/
int		is_arg_numeric(char *word);

/* builtin_utils.c*/
int		ft_atol(const char *nptr);
int		check_tiret_n(char *str);
void	dollar_interro(char **str, int i);
int		exit_1(t_env *env, char **argv, char *word, t_list *args);
void	change_path(t_list *env, char *oldpath, char *path);

/*env_utils2.c*/
void	to_next_node(t_list **tmp, t_list **node, char *str);
void	free_node_and_equal(t_list *node, char *str);
int		bigger_str(char *str1, char *str2);

/*builtin_utils2.c*/
char	*find_before_equal(char *str);
int		is_var(char *str);
void	multi_unset(t_env *env, char **str);
void	multi_export(t_env *env, char **str);

#endif
