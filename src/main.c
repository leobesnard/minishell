/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:18:39 by rmorel            #+#    #+#             */
/*   Updated: 2022/06/08 15:00:18 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *command_buf;

int	main()
{
	while (1)
	{
		command_buf = readline("minishell> ");
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
	}
	return (0);
}
