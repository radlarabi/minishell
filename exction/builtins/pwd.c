/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:15:05 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/11 13:04:02 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd_line **commands_v)
{
	(void)commands_v;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd,1);
		return(EXIT_SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return 1;
	}
	return 1;
}
