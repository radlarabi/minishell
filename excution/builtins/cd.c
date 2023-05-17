/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:52 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/17 16:27:39 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    cd_utils_1(char *perv_dir, char ***path)
{
    char    cwd[1024];

    if (!perv_dir)
    {
        ft_putendl_fd("cd: OLDPWD not set", 1);
        g_gv->exit_status = 1;
        return (-1);
    }
    else
    {
        **path = ft_getenv("OLDPWD");
        change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
        if (chdir(**path) == 0)
        {
            ft_putendl_fd(**path, 1);
            g_gv->exit_status = 0;
        }
        return (1);
    }
}

int    cd_utils(char **path, char *home_dir,char    **prev_dir)
{
    char    cwd[1024];

    *prev_dir = ft_getenv("OLDPWD");
    if (!(*path) || *path[0] == '~')
    {
        *path = home_dir;
        change_value(&g_gv->env, "OLDPWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
		return 1;
	}
    else if (*path[0] == '-')
        cd_utils_1(*prev_dir, &path);
    return (0);
}

int    ft_cd(t_cmd_line **cd_cmd)
{
    char    *home_dir;
    char    *path;
    char    cwd[1024];
    char    *prev_dir;

    home_dir = ft_getenv("HOME");
    path = (*cd_cmd)->cmds[1];
    prev_dir = NULL;
  	if (!cd_utils(&path, home_dir,&prev_dir))
		return 0;
    if (!home_dir)
    {
        ft_putendl_fd("cd: HOME not set", 1);
        g_gv->exit_status = 1;
        return (-1);
    }
    if (chdir(path) != -1)
    {
        prev_dir = ft_getenv("OLDPWD");
        change_value(&g_gv->env, "OLDPWD",ft_strdup(prev_dir));
        g_gv->exit_status = 0;
        return (0);
    }
    else if (g_gv->exit_status < 1)
    {
        g_gv->exit_status = 1;
        perror("chdir");
    }
    g_gv->exit_status = 0;
    return (0);
}
