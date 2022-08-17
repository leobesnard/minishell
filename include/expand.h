/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:12:43 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/17 17:39:55 by rmorel           ###   ########.fr       */
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

int		test_check_quotes(char *str);
int 	test_size_expand(char *str, t_list *env);
void	var_incr(t_var *var);
char    *var_str(char *str);
int		get_var_size(char *str, t_list *env);
int		ft_is_var_char(int c);

#endif 
