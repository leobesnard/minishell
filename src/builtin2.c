/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbesnard <lbesnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:52:14 by lbesnard          #+#    #+#             */
/*   Updated: 2022/07/15 22:10:00 by lbesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (tab_size(args) == 0)
	{
		path = find_env_var(env, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strncmp(args[0], "-", 2) == 0)
	{
		path = find_env_var(env, "OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD no set\n");
			return (NULL);
		}
	}
	else
		path = args[0];
	return (path);
}

int	change_pwd(t_list *env, char *path, char *oldpath)
{
	char	*tmp;
	char	*var;
	
	var = ft_strjoin("OLDPWD=", oldpath);
	if (!var)
		return (1);
	if (find_env_var(env, "OLDPATH"))
		builtin_export(env, )
	return (0);
}

int	builtin_cd(t_list *env, char **args)
{
	char	*str;
	char	*path;
	char	*oldpath;
	
	if (tab_size(args) >= 2)
		return (write(2, "cd : too many arguments\n", 24));
	path = get_cd_path(env, args);
	if (!path)
		return (1);
	if (access(path, F_OK))
		return (ft_printf("cd: no such file or directory"));
	if (access(path, X_OK))
		return (ft_printf("cd: permission denied: %s", path));
	oldpath = getcwd(0, 0);
	chdir(path);
	change_pwd(env, path, oldpath);
	free(oldpath);
	
}
