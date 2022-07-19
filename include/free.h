/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:57:51 by lbesnard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/19 20:50:55 by rmorel           ###   ########.fr       */
=======
/*   Updated: 2022/07/12 12:44:22 by rmorel           ###   ########.fr       */
>>>>>>> 095dfecf715f171790e8ed71f2b219053c9da822
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "libft.h"

/* free */
t_list	*free_token_list(t_list **list);
char	**free_ptr(char **ptr);
void	free_env(char **env);
void	free_array(char ***args);
void	free_parsed(t_list **parsed);

#endif
