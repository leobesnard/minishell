/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/13 22:59:49 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static char	*get_input_from_prompt(void);

int	main(int argc, char **argv, char **envp)
{
	t_list	*lexed;
	t_list	*parsed;
	t_env	*env;
	char	*command_buf;
	int		ret;

	env = create_struct_env(envp);
	if (argc != 1)
	{
		ret = first_command(argc, argv);
		return (ret);
	}
	parsed = NULL;
	while (1)
	{
		signal_management(NORMAL);
		command_buf = get_input_from_prompt();
		command_buf = expand(env->envdup, command_buf);
		env->command_buf = command_buf;
		if (!command_buf)
		{
			env->parsed = NULL;
			builtin_exit(parsed, env, NULL, NULL);
		}	
		if (test_check_quotes(command_buf))
		{
			printf("Error quote\n");
		}
		else
		{
			lexed = lexer(command_buf);
			//printf("in main : %s\n", lexed->content->word);
			if (lexed)
			{
				ret = create_cmd_list(lexed, &parsed);//lst_size(lexer) = 4 avant et = 2 apres donc tu perd des maillonts dedans
				env->parsed = parsed;
				if (ret != 0)
					print_error(ret);
				else
				{	
					ret = execute_command(parsed, env);
					if (ret != 0)
						print_error(ret);
					free_parsed(&parsed);
				}
			}
		}
		free(command_buf);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}

static char	*get_input_from_prompt(void)
{
	char	*command_buf;

	if (isatty(STDIN_FILENO))
		command_buf = readline("minicheh> ");
	else
		command_buf = get_next_line(STDIN_FILENO);
	if (!command_buf)
		return (NULL);
	else if (isatty(STDIN_FILENO) && command_buf && command_buf[0])
		add_history(command_buf);
	return (command_buf);
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
