/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/12 16:29:13 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_minishell;

int	main(int ac, char **av)
{
	t_list	*test;
	t_list	*parsed;
	char	*command_buf;
	int		ret;
	struct termios	termios_new;

	/*if (ac != 1)
	  {
	  execute_command(create_cmd_list(lexer(group_av(ac, av))));
	  return (0);
	  }*/
	if (tcgetattr(0, &termios_new))
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("tcsetattr");
		exit(1);
	}
	signal_management();
	parsed = NULL;
	g_minishell = malloc(sizeof(t_minishell));
	if (!g_minishell)
		return (MEM_ERROR);
	ft_bzero(g_minishell, sizeof(t_minishell));
	while (1)
	{
		command_buf = readline("minishell> ");
		if (!ft_strncmp(command_buf, "quit", 5))
		{
			free(g_minishell);
			return (0);
		}
		test = lexer(command_buf);
		ret = create_cmd_list(test, &parsed);
		if (ret != 0)
			print_error(ret);
		else
		{	
			execute_command(parsed);
			free_parsed(&parsed);
		}
		free(command_buf);
	}
	(void)ac;
	(void)av;
	return (0);
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
