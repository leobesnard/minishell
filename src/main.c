/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/09/22 22:33:25 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static char	*get_input_from_prompt(void);

void	print_lexer(t_list *lexer)
{
	while (lexer)
	{
		ft_printf("%s\n", ((t_token *)lexer->content)->word);
		lexer = lexer->next;
	}
}

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
		printf("No arguments\n");
		return (-1);
	}
	parsed = NULL;
	while (1)
	{
		env->quote_flag = 0;
		signal_management(NORMAL);
		command_buf = get_input_from_prompt();
		if (!command_buf)
		{
			env->parsed = NULL;
			builtin_exit(parsed, env, NULL, NULL);
		}	
		else
		{
			lexed = lexer(command_buf, &env->quote_flag);
		//	print_lexer(lexed);
			if (lexed)
			{
				pass_expand(&lexed, env);
				remove_empty(lexed);
			}
			if (env->quote_flag)
				ft_printf("Unmatching quote\n");
			else if (lexed)
			{
				if (parser(lexed, &parsed) == MEM_ERROR)
					print_error(MEM_ERROR);
				env->parsed = parsed;
				ft_lstclear(&lexed, &free_token);
				ret = execute_command(parsed, env);
				if (ret != 0)
					print_error(ret);
			}
		}
		free(command_buf);
		free_parsed(&parsed);
	}
	return (0);
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

	if (isatty(STDIN_FILENO))
		command_buf = readline("minicheh> ");
	else
		command_buf = readline("minicheh> ");
		//command_buf = get_next_line(STDIN_FILENO);
	if (!command_buf)
		return (NULL);
	else if (isatty(STDIN_FILENO) && command_buf && command_buf[0])
		add_history(command_buf);
	return (command_buf);
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
