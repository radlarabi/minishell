/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:15:05 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/27 00:54:09 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_command **cmd)
{
	t_command *tmp;
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

void	commands(t_command **commands_v)
{
	t_command *temp;
	temp = *commands_v;

}
