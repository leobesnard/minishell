/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:23:04 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/29 12:25:49 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TOOLS_H
# define PRINT_TOOLS_H

void	print_cmd(t_list *list);
void	print_token_list(t_list *list, char *str);
void	print_tab(char **tab, char *str);
void	print_cmd_fd(t_cmd_fd *cmd_fd, char *str);

#endif
