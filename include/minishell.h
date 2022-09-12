/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:19:28 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/12 17:09:33 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MEM_ERROR -42
# define SYNTAX_ERROR -10
# define PIPE_ERROR -20
# define FD_ERROR -30
# define SIGINT_HEREDOC -50
# define CHILD 1
# define HEREDOC 2
# define NORMAL 0

# include <assert.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "command.h"
# include "builtin.h"
# include "env.h"
# include "free.h"
# include "print_tools.h"
# include "signal_minishell.h"
# include "expand.h"

//	main.c

int		first_command(int ac, char **av);
char	*group_av(int ac, char **av);
void	print_error(int ret);

#endif
