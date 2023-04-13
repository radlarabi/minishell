/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:15:05 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/04/13 14:43:26 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_pwd(t_cmd_line **commands_v,t_command **cmd)
{
	t_command *tmp;
	(void)commands_v;
	char cwd[1024];
	tmp = *cmd;
	if (tmp && !ft_strncmp(tmp->content, "pwd", 3))
	{

		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s\n", cwd);
			return(EXIT_SUCCESS);
		}
		else {
			perror("getcwd() error");
			return 1;
		}
	}
	return 1;
}

void	commands(t_cmd_line **commands_v,t_command **cmd)
{
}
