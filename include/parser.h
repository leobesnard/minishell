/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:10:17 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/13 20:37:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char			**arg;
	char			*outfile;
	int				append_outfile;
	char			*infile;
	char			*errfile;
	struct s_cmd	*next;
}	t_cmd;

int	fill_cmd(t_cmd *cmd, t_list *list);

#endif
