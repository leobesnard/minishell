/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:19:28 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 19:02:42 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <assert.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "command.h"
# include "print_tools.h"
# include "free.h"
# include "env.h"
# include "builtin.h"

typedef struct s_global_var
{
	t_list	*trash;
}	t_global_var;

#endif
