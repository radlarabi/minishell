/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:15:05 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/21 19:07:57 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd_line **commands_v)
{
	char	cwd[1024];

	if (((*commands_v)->infile == -1 && (*commands_v)->flag == 3)
		|| ((*commands_v)->outfile == -1 && (*commands_v)->flag == 4))
		return (1);	
	(void)commands_v;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		g_gv->exit_status = 0;
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("pwd");
		g_gv->exit_status = 1;
		return (1);
	}
	g_gv->exit_status = 0;
	return (1);
}
