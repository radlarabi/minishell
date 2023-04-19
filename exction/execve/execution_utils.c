/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:32:08 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/04/19 17:04:16 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_execution(t_cmd_line *cmd_l)
{
	if (!ft_strcmp(cmd_l->cmds[0],"echo"))
			ft_echo(&cmd_l);
	else if (!ft_strcmp(cmd_l->cmds[0],"pwd"))
			ft_pwd(&cmd_l);
	else if (!ft_strcmp(cmd_l->cmds[0],"cd"))
			ft_cd(&cmd_l);
	else
	{
		execve(get_path_command(get_path(g_gv->env), cmd_l->cmds[0]), cmd_l->cmds, NULL);
		perror("execve");
	}
}
