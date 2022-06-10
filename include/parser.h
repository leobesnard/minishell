/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:10:17 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/10 23:34:52 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_simple_cmd
{
	char			*arg;
	s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_cmd
{
	t_simple_cmd	*s_cmd;
	s_cmd			*next;
}

/*		CAS COMPLIQUE

typedef struct s_simple_cmd
{
	t_cmd_prefix		*cmd_prefix;
	char				*cmd_word;
	char				*cmd_name;
	t_cmd_suffix		*cmd_suffix;
	struct s_simple_cmd	*prev;
	struct s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_io_file
{
	t_operator 	io_file_operator;
	char		*file_name;
}	t_io_file;

typedef struct io_redirect
{
	t_io_file	*io_file;
	int			IO_NUMBER;
}	t_io_redirect;

typedef struct s_cmd_prefix
{
	t_io_redirect		*io_redirect;
	char				*ass_word;
	struct s_cmd_prefix	*next;
}	t_cmd_prefix;

typedef struct s_cmd_suffix
{
	t_io_redirect		*io_redirect;
	char				*word;
	struct s_cmd_prefix	*next;
}	t_cmd_suffix;

*/

#endif
