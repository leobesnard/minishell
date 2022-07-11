/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/07/11 16:32:46 by lbesnard         ###   ########.fr       */
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

	env = dup_env(envp);
	printf("===============\nDEBUT DES TESTS DE LEO\n");
	printf("\n~~~Test du builtin PWD~~~\n");
	builtin_pwd(env);
	printf("\n~~~Test du builtin env~~~\n");
	builtin_env(env);
	printf("\n~~~Test du builtin unset~~~\n");
	printf("%s\n~Suppression de la variable USER~\n", find_env_var(env, "USER"));
	env = builtin_unset(env, "USER");
	if (find_env_var(env, "USER"))
		printf("%s\n", find_env_var(env, "USER"));
	else
		printf("variable inexistante\n");
	printf("\n~~~Test du builtin export~~~\n");
	if (find_env_var(env, "LOGNAME"))
		printf("%s\n~Creation de la variable LOGNAME=rmorel~\n", find_env_var(env, "LOGNAME"));
	else
		printf("variable inexistante\n~Creation de la variable LOGNAME=rmorel~\n");
	env = builtin_export(env, "LOGNAME=rcarles\n");
	printf("%s\n", find_env_var(env, "LOGNAME"));
	
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
	(void)argc;
	(void)argv;
	return (0);
}
