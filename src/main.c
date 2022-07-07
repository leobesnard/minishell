/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/07 18:19:23 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_list	*test;
	t_list	*parsed;
	char	*command_buf;
	int		ret;

	/*if (ac != 1)
	{
		execute_command(create_cmd_list(lexer(group_av(ac, av))));
		return (0);
	}*/
	parsed = NULL;
	while (1)
	{
		command_buf = readline("minishell> ");
		test = lexer(command_buf);
		//printf("env = %s\n", getenv("PATH"));
		print_token_list(test, "token");
		ret = create_cmd_list(test, &parsed);
		if (ret != 0)
			print_error(ret);
		else
		{
			print_cmd(parsed);
			execute_command(parsed);
		}
	}
	(void)ac;
	(void)av;
	return (0);
}

void	print_error(int ret)
{
	if (ret == MEM_ERROR)
		printf("Memory error, get yourself another computer now.\n");
	else if (ret == SYNTAX_ERROR)
		printf("Syntax error, go back to SHELL00.\n");
	else if (ret == PIPE_ERROR)
		printf("Can't create a pipe correctly, call a plumber.\n");
	else if (ret == FD_ERROR)
		printf("Can't access to the file given in parameter.\n");
}

char	*group_av(int ac, char **av)
{
	int		sz;
	int		i;
	int		j;
	int		k;
	char	*str;

	sz = 0;
	i = 0;
	j = 0;
	k = 0;
	while (i++ < ac - 1)
	{
		sz += ft_strlen(av[i]);
	}
	str = malloc(sz + ac - 2 + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		while (av[i][k])
		{
			str[j] = av[i][k];
			j++;
			k++;
		}
		i++;
		if (i < ac)
			str[j] = ' ';
		j++;
		k = 0;
	}
	str[j] = '\0';
	return (str);
}		
