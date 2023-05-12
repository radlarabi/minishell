/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:52 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/12 14:56:17 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_oldpwd(t_env **env)
{
	t_env	*temp;
	char	cwd[1024];

	temp = (*env);
	while (temp->next)
	{
		if (!ft_strcmp(temp->var, "OLDPWD"))
			temp->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
		temp = temp->next;
	}
	return (NULL);
}

int	ft_cd(t_cmd_line **cd_cmd)
{
	char	*home_dir;
	char	*prev_dir;
	char	cwd[1024];
	char *path;
	home_dir = ft_getenv("HOME");
	prev_dir = ft_getenv("OLDPWD");
	path = (*cd_cmd)->cmds[1];
	if (!path|| *path == '~')
	{
		path = home_dir;
		change_value(&g_gv->env, "OLDPWD",ft_strdup(getcwd(cwd, sizeof(cwd))));
	}
	else if (*path == '-')
	{
		if (!prev_dir)
		{
			ft_putendl_fd("cd: OLDPWD not set",1);
			g_gv->exit_status = 1;
			return (-1);
		}
		else
		{
			path = ft_getenv("OLDPWD");
			change_value(&g_gv->env, "OLDPWD",ft_strdup(getcwd(cwd, sizeof(cwd))));
			if (chdir(path) == 0)
			{
				ft_putendl_fd(path, 1);
				g_gv->exit_status = 0;
			}
			return 1;
		}
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		g_gv->exit_status = 1;
		return (-1);
	}
	g_gv->exit_status = 0;
	// exit(0);
	return (0);
}
