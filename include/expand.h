/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:12:43 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/21 19:05:17 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

typedef struct	s_var
{
	int		i;
	int		sz;
	char	*str;
}	t_var;

typedef struct	s_vars
{
	int		i;
	int		u;
	char	*ret;
	char	*var;
	char	*str;
}	t_vars;

char	*expand(t_list *env, char *str, int *flag);
int		size_expand(char *str, t_list *env);
int		test_check_quotes(char *str);
int 	test_size_expand(char *str, t_list *env);
void	var_incr(t_var *var);
char    *var_str(char *str);
int		get_var_size(char *str, t_list *env);
int		ft_is_var_char(int c);

/*expand_utils*/
void	incr(char *str, t_vars *var);

/*expand_utils2.c*/
void	expand_simple_quotes(char *str, t_vars *var);
void	expand_dollar(t_vars *var, t_list *env, char *str);
void	expand_double_quotes(t_vars *var, t_list *env, char *str);
int		init_expand(t_vars *var, char *str, t_list *env);

/*expand_utils3.c*/
void	dollar_size(t_var *var, char *str, t_list *env);
void	simple_quote_size(t_var *var, char *str);
void	double_quote_size(t_var *var, char *str, t_list *env);

#endif 
