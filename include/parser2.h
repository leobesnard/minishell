/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:37:52 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/15 15:41:38 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H

typedef enum e_cmd_type;
{
	CMD,
	PIPE,
}	t_cmd_type;

typedef struct s_node
{
	t_cmd_type	type;
	t_list		*arg;
	t_list		*rd;

}	t_node;

#endif
