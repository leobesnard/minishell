/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:19:28 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 16:15:18 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SYNTAX_ERROR -10
# define PIPE_ERROR -20
# define FD_ERROR -30
# define MEM_ERROR -42
# define SIGINT_HEREDOC -50
# define CMD_NOT_FOUND -60
# define CHILD 1
# define HEREDOC 2
# define NORMAL 0
# define CMD_BUILTIN 1
# define CMD_PATH_BINARY 2

# include <assert.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
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

typedef struct s_big
{
	t_list	*lexed;
	t_list	*parsed;
	t_env	*env;
	char	*command_buf;
	int		ret;
}	t_big;

//	main.c

int		first_command(int ac, char **av);
char	*group_av(int ac, char **av);
void	print_error(int ret);
int		pass_expand(t_list **lexer, t_env *env);

#endif
