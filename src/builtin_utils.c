/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:39:49 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/22 23:02:00 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] && ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == 32))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (sign * res);
}

int	check_tiret_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	dollar_interro(char **str, int i)
{
	str[i] += 2;
	ft_printf("%d%s", g_minishell.last_exec_code, str[i]);
	if (str[i + 1])
		ft_printf(" ");
}

int	exit_1(t_env *env, char **argv, char *word, t_list *args)
{
	int	ret;

	if (word)
	{
		if (!is_arg_numeric(word))
			return (free_before_exit(env, argv, env->cmd_fd),
				ft_putstr_fd("exit: numeric argument required\n", 2),
				exit(2), 2);
	}
	if (args && args->next)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	if (!args)
	{
		free_before_exit(env, argv, env->cmd_fd);
		exit(g_minishell.last_exec_code);
	}
	else
	{
		ret = ft_atol(word);
		free_before_exit(env, argv, env->cmd_fd);
		exit((unsigned int)ret);
	}
	return (0);
}

void	change_path(t_list *env, char *oldpath, char *path)
{
	oldpath = getcwd(0, 0);
	chdir(path);
	change_pwd(env, path, oldpath);
	free(oldpath);
}
