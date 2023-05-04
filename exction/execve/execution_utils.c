/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:32:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/04 21:26:56 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




char *get__path(char *cmd)
{
	t_env *tmp = g_gv->env;
	int i = 0;
	int j = 0;
	char **path;
	while(tmp)
	{
		printf("tmp->var %s\n", tmp->var);
		if (!ft_strcmp(tmp->var, "PATH"))
		{
			path = ft_split(tmp->value, ':');
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
	while(path && path[i])
	{
		if (access(ft_strjoin(path[i], cmd), F_OK) != -1)
		{
			return ft_strjoin(path[i], cmd);
		}
		i++;
	}
	return NULL;
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
		else if (!ft_strcmp(cmd_l->cmds[0],"exit"))
			exit(0);
		else
		{
			if (cmd_l->cmds && ft_strchr(cmd_l->cmds[0], '/'))
			{
				printf("sec execve\n");
				execve(cmd_l->cmds[0], cmd_l->cmds, NULL);
				perror("execve cmd[0]");
			}
			
			


			
			path = get__path(cmd_l->cmds[0]);
			printf("path is %s\n", path);
			if (access(path, F_OK) == -1 || !ft_strcmp(cmd_l->cmds[0], ""))
			{
				printf("command not found : %s\n", cmd_l->cmds[0]);
				exit(127);
			}
			printf("main execve\n");
			execve(path , cmd_l->cmds, get_path(&g_gv->env));
			perror("execve");
		}
	}
}
