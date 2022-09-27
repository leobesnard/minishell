/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/27 17:50:47 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static char	*get_input_from_prompt(void);
static void	loop_start(t_env *env);
static void	loop_else(t_big *big);

int	main(int argc, char **argv, char **envp)
{
	t_big	big;	

	big.env = create_struct_env(envp);
	if (argc != 1)
		return (printf("No arguments\n"), -1);
	big.parsed = NULL;
	while (1)
	{
		loop_start(big.env);
		big.command_buf = get_input_from_prompt();
		if (!big.command_buf)
		{
			big.env->parsed = NULL;
			builtin_exit(big.parsed, big.env, NULL, NULL);
		}	
		else
			loop_else(&big);
		free(big.command_buf);
		free_parsed(&big.parsed);
		(void)argv;
	}
	return (0);
}

static void	loop_else(t_big *big)
{
	big->lexed = lexer(big->command_buf, &big->env->quote_flag);
	if (big->lexed)
	{
		pass_expand(&big->lexed, big->env);
		remove_empty(big->lexed);
	}
	if (big->env->quote_flag)
		ft_printf("Unmatching quote\n");
	else if (big->lexed)
	{
		if (parser(big->lexed, &big->parsed) == MEM_ERROR)
			print_error(MEM_ERROR);
		big->env->parsed = big->parsed;
		ft_lstclear(&big->lexed, &free_token);
		big->ret = execute_command(big->parsed, big->env);
		if (big->ret != 0)
			print_error(big->ret);
	}
}

static void	loop_start(t_env *env)
{
	env->quote_flag = 0;
	signal_management(NORMAL);
}

int	pass_expand(t_list **lexer, t_env *env)
{
	t_list	*lst;

	lst = *lexer;
	while (lst)
	{
		((t_token *)lst->content)->word = expand(env->envdup,
				((t_token *)lst->content)->word, &env->quote_flag);
		if (!((t_token *)lst->content)->word)
			return (-1);
		lst = lst->next;
	}
	return (0);
}

static char	*get_input_from_prompt(void)
{
	char	*command_buf;

	command_buf = readline("minicheh> ");
	if (!command_buf)
		return (NULL);
	else if (isatty(STDIN_FILENO) && command_buf && command_buf[0])
		add_history(command_buf);
	return (command_buf);
}
