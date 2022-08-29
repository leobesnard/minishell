/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:12:43 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/29 16:23:02 by lbesnard         ###   ########.fr       */
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

char	*expand(t_list *env, char *str);
int		test_check_quotes(char *str);
int 	test_size_expand(char *str, t_list *env);
void	var_incr(t_var *var);
char    *var_str(char *str);
int		get_var_size(char *str, t_list *env);
int		ft_is_var_char(int c);

#endif 
