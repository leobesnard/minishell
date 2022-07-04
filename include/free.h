/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:57:51 by lbesnard          #+#    #+#             */
/*   Updated: 2022/06/22 22:48:52 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "libft.h"

/* free */
t_list	*free_list(t_list **list);
char	**free_ptr(char **ptr);
void	free_env(char **env);

#endif