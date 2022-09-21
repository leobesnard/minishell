/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:52:14 by lbesnard          #+#    #+#             */
/*   Updated: 2022/09/21 21:26:20 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*get_cd_path(t_list *env, char **args)
{
	char	*path;

	if (tab_size(args) == 1)
	{
		path = find_env_var(env, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = find_env_var(env, "OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD no set\n");
			return (NULL);
		}
	}
	else
		path = args[1];
	return (path);
}

int	change_pwd(t_list *env, char *path, char *oldpath)
{
	char	*var;

	var = ft_strjoin("OLDPWD=", oldpath);
	if (!var)
		return (1);
	if (find_env_var(env, "OLDPWD"))
		builtin_export(env, "OLDPWD");
	free(var);
	var = ft_strjoin("PWD=", path);
	if (!var)
		return (1);
	if (find_env_var(env, "PWD"))
		builtin_export(env, "PWD");
	free(var);
	return (0);
}

int	builtin_cd(t_list *env, char **args)
{
	char	*path;
	char	*oldpath;

	if (tab_size(args) >= 3)
	{
		g_minishell.last_exec_code = 1;
		return (write(2, "cd : too many arguments\n", 24));
	}
	path = get_cd_path(env, args);
	if (!path)
		return (1);
	if (access(path, F_OK))
	{
		g_minishell.last_exec_code = 1;
		return (ft_printf("cd: no such file or directory\n"));
	}
	if (access(path, X_OK))
	{
		g_minishell.last_exec_code = 1;
		return (ft_printf("cd: permission denied: %s\n", path));
	}
	change_path(env, oldpath, path);
	return (0);
}
