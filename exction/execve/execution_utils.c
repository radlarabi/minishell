/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:32:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/09 13:04:01 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get__path(char *cmd)
{
	t_env *tmp = g_gv->env;
	int i = 0;
	char **path;

	path = NULL;
	while(tmp)
	{
		if (!ft_strcmp(tmp->var, "PATH"))
		{
			path = ft_split(tmp->value, ':');
			if (!path)
				return NULL;
			break;
		}
		tmp = tmp->next;
	}
	while(path && path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	i = 0;
	cmd = set_spliter(cmd, ' ');
	char **temp = ft_split(cmd, -1);
	while(path && path[i])
	{
		char *ttt;
		path[i] = ft_strjoin(path[i], temp[0]);
		if (access(path[i], F_OK) != -1)
			return path[i];
		i++;
	}
	return NULL;
}

char **get__env()
{
	t_env *tmp;
	char **ret;
	int i = 0;
    tmp = g_gv->env;
    while(tmp)
    {
		i++;
        tmp = tmp->next;
    }
	ret = malloc(sizeof(char *) * (i + 1));
	tmp = g_gv->env;
	i = 0;
	while(tmp)
	{
		ret[i] = NULL;
		ret[i] = ft_strjoin(ret[i], tmp->var);
		ret[i] = ft_strjoin(ret[i], "=");
		ret[i] = ft_strjoin(ret[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	ret[i] = 0;
	return ret;
}

void ft_execution(t_cmd_line *cmd_l)
{
	char *path;
	if (cmd_l->cmds[0])
	{
		if (!ft_strcmp(cmd_l->cmds[0],"echo"))
			ft_echo(&cmd_l);
		else if (!ft_strcmp(cmd_l->cmds[0],"pwd"))
			ft_pwd(&cmd_l);
		else if (!ft_strcmp(cmd_l->cmds[0],"cd"))
			ft_cd(&cmd_l);
		else if (!ft_strcmp(cmd_l->cmds[0],"env"))
			ft_env(&cmd_l);
		else if (!ft_strcmp(cmd_l->cmds[0],"export"))
			ft_export(&cmd_l);
		else
		{
			if (cmd_l->cmds && ft_strchr(cmd_l->cmds[0], '/'))
			{
				DIR *dir;
				dir = opendir(cmd_l->cmds[0]);
				if (dir != NULL)
				{
					printf("%s : is a directory\n", cmd_l->cmds[0]);
					exit(126);	
				}
				execve(cmd_l->cmds[0], cmd_l->cmds, get__env());
				perror("execve");
				exit(127);
			}

			path = get__path(cmd_l->cmds[0]);
			execve(path , cmd_l->cmds, get__env());
			perror("execve");
			exit(127);
		}
	}
}
