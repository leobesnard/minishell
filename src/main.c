/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/08/25 16:27:24 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	main(int argc, char **argv, char **envp)
{
//	t_list	*lexed;
//	t_list	*parsed;
	t_env	*env;
	char	*command_buf;
	int		ret;

	env = create_struct_env(envp);
	if (argc != 1)
	{
		ret = first_command(argc, argv);
		return (ret);
	}
//	signal_management(NORMAL);
//	parsed = NULL;
	while (1)
	{
		command_buf = readline("minishell> ");
		command_buf = expand(env->envdup, command_buf);
		if (command_buf == NULL)
			return (printf("quote problem\n"));
		printf("%s\n", command_buf);
		/*if (!command_buf)
		{
			printf("exit\n");
			return (0);
		}
		if (test_check_quotes(command_buf))
		{
			printf("Error quote\n");
		}
		else
			//printf("size = %d\n", test_size_expand(command_buf, env->envdup));
		{
			lexed = lexer(command_buf);
			if (lexed)
			{
				ret = create_cmd_list(lexed, &parsed);
				if (ret != 0)
				{
					print_error(ret);
					printf("error parsed\n");
					return (ret);
				}
				else
				{	
					ret = execute_command(parsed, env);
					if (ret != 0)
						print_error(ret);
					free_parsed(&parsed);
				}
			}
		}
		free(command_buf);*/
	}
	free_env(env);
	(void)argc;
	(void)argv;
	(void)envp;
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
	ret = execute_command(parsed, NULL);
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
