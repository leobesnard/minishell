/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:09:38 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/23 18:36:29 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

//		command.c

char	*get_path(char *arg);
void	free_all_except_one_str(char **array, int x);
int		execute_command(t_list *parsed);
char	**get_args(t_list *list);

//		list_utils.c

int		size_list(t_list *list);
void	free_array(char **args);
char	*concat_path(char *dest, char *src);

#endif
