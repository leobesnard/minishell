/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/13 21:41:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	t_list *test;
	t_list *parsed;
	char *command_buf;

	command_buf = readline("minishell> ");
	test = lexer(command_buf);
	parsed = create_cmd_list(test);
	while (1)
	{
		while (test)
		{
			t_token *token = test->content;
			printf("[%s] type = %d\n", token->word, token->type);
			test = test->next;
		}
		while (parsed)
		{
			t_cmd	*cmd = parsed->content;
			printf("[%s]\n", cmd->arg[0]);
			printf("[%s]\n", cmd->arg[1]);
			parsed = parsed->next;
		}
		command_buf = readline("minishell> ");
		test = lexer(command_buf);
		parsed = create_cmd_list(test); 
	}
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
