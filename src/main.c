/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/19 19:14:17 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	main(int ac, char **av)
{
	t_list	*lexed;
	t_list	*parsed;
	char	*command_buf;
	int		ret;

	if (ac != 1)
	{
		ret = first_command(ac, av);
		return (ret);
	}
	signal_management();
	parsed = NULL;
	while (1)
	{
		command_buf = readline("minishell> ");
		if (!command_buf)
		{
			printf("exit\n");
			return (0);
		}
		lexed = lexer(command_buf);
		ret = create_cmd_list(lexed, &parsed);
		if (ret != 0)
		{
			print_error(ret);
			return (ret);
		}
		else
		{	
			ret = execute_command(parsed);
			if (ret != 0)
				print_error(ret);
			free_parsed(&parsed);
		}
		free(command_buf);
	}
	(void)ac;
	(void)av;
	return (0);
}

int	first_command(int ac, char **av)
{
	char 	*grouped;
	t_list	*lexed;
	t_list	*parsed;
	int		ret;

	parsed = NULL;
	grouped = group_av(ac, av);
	lexed = lexer(grouped);
	ret = create_cmd_list(lexed, &parsed);
	if (ret != 0)
	{
		print_error(ret);
		return (ret);
	}
	ret = execute_command(parsed);
	if (ret != 0)
		print_error(ret);
	free_parsed(&parsed);
	return (ret);
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
