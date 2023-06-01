/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:32:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/06/01 15:16:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_utils(char **path)
{
	t_env	*tmp;

	tmp = g_gv->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PATH"))
		{
			path = ft_split(tmp->value, ':');
			if (!path)
				return (NULL);
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

char	*get__path(char *cmd)
{
	int		i;
	char	**path;

	i = 0;
	path = ft_utils(NULL);
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	i = 0;
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) != -1)
			return (path[i]);
		i++;
	}
	return (NULL);
}

void	fill_get_env(char **ret)
{
	t_env	*tmp;
	int		i;

	tmp = g_gv->env;
	i = 0;
	while (tmp)
	{
		ret[i] = NULL;
		ret[i] = ft_strjoin(ret[i], tmp->var);
		ret[i] = ft_strjoin(ret[i], "=");
		ret[i] = ft_strjoin(ret[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	ret[i] = 0;
}

char	**get__env(void)
{
	t_env	*tmp;
	char	**ret;
	int		i;

	i = 0;
	tmp = g_gv->env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	fill_get_env(ret);
	return (ret);
}

void	ft_execution(t_cmd_line *cmd_l)
{
	char	*path;

	if (cmd_l->cmds[0])
	{
		if (!check_command_builtins(cmd_l->cmds[0]))
		{
			command_builtins(&cmd_l, 1);
			exit(g_gv->exit_status);
		}
		else
		{
			ft_utils_1(cmd_l->cmds);
			path = get__path(cmd_l->cmds[0]);
			execve(path, cmd_l->cmds, get__env());
			perror(cmd_l->cmds[0]);
			exit(127);
		}
	}
}
