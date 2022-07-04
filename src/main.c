/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/04 17:59:07 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_list	*test;
	t_list	*tmp;
	t_list	*parsed;
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
	return (0);
}
