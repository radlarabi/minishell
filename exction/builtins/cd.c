/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:07:52 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/04/19 17:09:48 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_oldpwd(t_cmd_line **cd_cmd,t_env **env)
{
	t_env *temp;
	temp = (*env);
	char		cwd[1024];
	while (temp->next)
	{
		//printf("%s\n",temp->var);
		if (!ft_strcmp(temp->var,"OLDPWD"))
		 	temp->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
		temp = temp->next;
	}
	return NULL;
}

int	ft_cd(t_cmd_line **cd_cmd)
{

	char		*directory;
	struct stat	st;
	int			i;
	char		cwd[1024];
	static int j;

	i = 0;
	directory = (*cd_cmd)->cmds[1];
	if (directory && !ft_strcmp(directory, "/"))
		chdir(directory);
	else if((directory && !ft_strcmp(directory, "-")))
	{
		if(!j)
		{
			j = 1;
			get_oldpwd(cd_cmd,&g_gv->env);
			//g->value = getcwd(cwd, sizeof(cwd));
			ft_putendl_fd("cd: OLDPWD not set",1);
		}
		else
			chdir(g_gv->env->value);
	}
	else if (!directory || !ft_strcmp(directory, "~") || !ft_strcmp(directory, " "))
		chdir(getenv("HOME"));
	else if (stat(directory, &st) == -1)
		perror("Error");
	else if ((chdir(directory)) != 0)
		perror("Error");
	return (0);
}
