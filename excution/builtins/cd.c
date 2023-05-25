/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:52 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/25 20:59:18 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_utils_1(char *prev_dir, char **path, int *flag)
{
	char	cwd[1024];

	if (!prev_dir)
	{
		ft_putendl_fd("cd: OLDPWD not set", 1);
		g_gv->exit_status = 1;
		return (0);
	}
	else
	{
		*path = ft_strdup(prev_dir);
		(*flag) = 1;
		change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
		if (chdir(*path) == 0)
		{
			ft_putendl_fd(*path, 1);
			g_gv->exit_status = 0;
		}
		return (1);
	}
}

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
	return (new_path);
}

int	cd_utils(char **path, char *home_dir, char **prev_dir, int *flag)
{
	char	cwd[1024];

	*prev_dir = ft_getenv("OLDPWD");
	if (!(*path) || *path[0] == '~')
	{
		*path = ft_get_home_phat(home_dir, *path);
		(*flag) = 1;
		change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
		return (1);
	}
	else if (*path[0] == '-')
		return (cd_utils_1(*prev_dir, &(*path), flag));
	else if (*path)
	{
		change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
		return (1);
	}
	return (0);
}

int	home_not_set_cd(char *home_dir)
{
	if (!home_dir)
	{
		ft_putendl_fd("cd: HOME not set", 1);
		g_gv->exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_cmd_line **cd_cmd)
{
	char	*home_dir;
	char	*path;
	char	*prev_dir;
	int		flag;

	flag = 0;
	home_dir = ft_getenv("HOME");
	path = (*cd_cmd)->cmds[1];
	prev_dir = NULL;
	if (!cd_utils(&path, home_dir, &prev_dir, &flag))
		return ;
	if (cd_utils_2(path, prev_dir, flag))
		return ;
	else if (path && g_gv->exit_status < 1 && flag != 1)
	{
		g_gv->exit_status = 1;
		perror("chdir");
		return ;
	}
	if (home_not_set_cd(home_dir))
	{
		free(path);
		return ;
	}
}
