/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/15 22:20:33 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*test;
	t_list	*tmp;
	t_list	*parsed;
	t_list	*env;
	char	*command_buf;

	while (1)
	{
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
	}
	free_env(env);
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
