/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:53:34 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/29 21:51:11 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int line_cmd(char **cmd)
{
	int len;
	len = 0;
	while (cmd[len])
		len++;
	return len;
}

int	ft_echo(t_cmd_line **commands_v,t_command **cmd)
{
	int			i;
	int			flag;
	(void)cmd;
	t_cmd_line *tmp;
	tmp = (*commands_v);
	flag = 0;
	i = 1;
	while (i < line_cmd(tmp->cmds))
	{
		while (tmp->cmds[i] && !ft_strncmp(tmp->cmds[i],"-n",ft_strlen(tmp->cmds[i])))
		{
			flag = 1;
			i++;
		}
		while (tmp->cmds[i])
		{
			ft_putstr_fd(tmp->cmds[i],1);
			i++;
		}
	}
	if (!flag)
		write(1,"\n",1);
	return (0);
}
