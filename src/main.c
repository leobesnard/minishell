/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/23 16:57:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main()
{
	t_list	*test;
	t_list 	*tmp;
	t_list	*parsed;
	char	*command_buf;

	command_buf = readline("minishell> ");
	test = lexer(command_buf);
	tmp = test;
	printf("env = %s\n", getenv("PATH"));
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
