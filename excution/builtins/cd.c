/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:52 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/28 01:37:38 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_home_phat(char *home, char *path)
{
	char	*new_path;
	char	*homet;

	homet = ft_strdup(home);
	if (!path)
		return (homet);
	new_path = NULL;
	if (homet && path)
		new_path = ft_strjoin(homet, path + 1);
	free(path);
	return (new_path);
}

int	cd_absolute_path(char *home_dir, char **path)
{
	char	cwd[1024];

	if (home_not_set_cd(home_dir))
	{
		free((*path));
		return (1);
	}
	(*path) = ft_get_home_phat(home_dir, (*path));
	change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
	return (0);
}

int	cd_prev_pwd(char **path)
{
	char	cwd[1024];
	char	*prev_pwd;

	prev_pwd = ft_getenv("OLDPWD");
	if (!prev_pwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 1);
		g_gv->exit_status = 1;
		free((*path));
		return (1);
	}
	free((*path));
	(*path) = ft_strdup(prev_pwd);
	if (prev_pwd[0])
	{
		ft_putendl_fd(prev_pwd, 1);
		change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
	}
	return (0);
}

void	change_directory(char **path)
{
	if (chdir((*path)) != -1)
	{
		g_gv->exit_status = 0;
		free((*path));
	}
	else
	{
		perror((*path));
		free((*path));
		g_gv->exit_status = 1;
	}
}

void	ft_cd(t_cmd_line **cd_cmd)
{
	char	*home_dir;
	char	*path;
	char	cwd[1024];

	home_dir = ft_getenv("HOME");
	if ((*cd_cmd)->cmds[1])
		path = ft_strdup((*cd_cmd)->cmds[1]);
	else
		path = NULL;
	if (!path || path[0] == '~')
	{
		if (cd_absolute_path(home_dir, &path))
			return ;
	}
	else if (path && path[0] == '-' && !path[1])
	{
		if (cd_prev_pwd(&path))
			return ;
	}
	else if (path)
		change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
	change_directory(&path);
}
