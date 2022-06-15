/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/15 23:40:26 by rmorel           ###   ########.fr       */
=======
/*   Updated: 2022/06/13 21:41:04 by rmorel           ###   ########.fr       */
>>>>>>> rmorel
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD


int	main()
{
	t_list	*test;
	t_list 	*tmp;
	t_list	*parsed;
	char	*command_buf;

	command_buf = readline("minishell> ");
	test = lexer(command_buf);
	tmp = test;
	while (test)
=======

int	main()
{
	t_list *test;
	t_list *parsed;
	char *command_buf;

	command_buf = readline("minishell> ");
	test = lexer(command_buf);
	parsed = create_cmd_list(test);
	while (1)
>>>>>>> rmorel
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
	test = tmp;
	parsed = create_cmd_list(test);
	printf("%p\n", parsed);
	while (parsed)
	{
		t_cmd *cmd = parsed->content;
		while (cmd->arg)
		{
			t_token *token2 = cmd->arg->content;
			printf("[%s]\n", token2->word);
			cmd->arg = cmd->arg->next;
		}
		printf("fin arg\n");
		while (cmd->rd)
		{
			t_token *token3 = cmd->rd->content;
			printf("[%s]\n", token3->word);
			cmd->rd = cmd->rd->next;
		}
		parsed = parsed->next;
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
