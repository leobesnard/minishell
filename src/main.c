/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 18:57:49 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_var global;

int	main(int argc, char **argv, char **envp)
{
	t_list	*test;
	t_list 	*tmp;
	t_list	*parsed;
	char	*command_buf;
	//char	**str;
	t_list	*env_dup;

	(void)argc;
	(void)argv;
	/* str = malloc(sizeof(*str) * 5);
	str[0] = "-n ";
	str[1] = "bonjour";
	str[2] = "comment";
	str[3] = "ca    va ?";
	str[4] = NULL; */
	global.trash = NULL;
	env_dup = dup_env(envp);
	command_buf = readline("minishell> ");
	test = lexer(command_buf);
	tmp = test;
	env_dup = add_var(env_dup, "BONJOUR=lol");
	printf("%s\n", find_env_var(env_dup, "BONJOUR"));
	//env_dup = del_var(env_dup, "BONJOUR");
	//env_dup = del_var(env_dup, "GJS_DEBUG_TOPICS");
	//printf("%s\n", find_env_var(env_dup, "GJS_DEBUG_TOPICS"));
	//echo(str);
	pwd(env_dup);
	env(env_dup);
	printf("\n\n\n");
	env_dup = unset(env_dup, "BONJOUR");
	env(env_dup);
	while (test)
	{
		t_token *token = test->content;
		printf("[%s] type = %d\n", token->word, token->type);
		test = test->next;
	}
	test = tmp;
	parsed = create_cmd_list(test);
	print_cmd(parsed);
	execute_command(parsed);
	/* while (1)
	   {
	   if(strlen(command_buf) > 0)
	   add_history(command_buf);
	   if (!strcmp(command_buf, "ifconfig"))
	   system("ifconfig");
	   else if (!strcmp(command_buf, "date"))
	   system("date");
	   else if (!strcmp(command_buf, "ls"))
	   system("ls");
	   else if (!strcmp(command_buf, "pwd"))
	   printf("%s\n", getcwd(command_buf, 1000));
	   else if (!strcmp(command_buf, "exit") || !strcmp(command_buf, "quit"))
	   break;
	   } */
	return (0);
}
