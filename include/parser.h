/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:10:17 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/14 15:41:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	int				nb_arg;
	char			**arg;
	char			*outfile;
	int				append_outfile;
	char			*infile;
	char			*errfile;
}	t_cmd;

t_cmd	*cmd_new(void);
t_list	*create_cmd_list(t_list *list);
int		fill_cmd(t_cmd *cmd, t_list *list);

#endif
