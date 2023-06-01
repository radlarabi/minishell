/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:55:12 by rlarabi           #+#    #+#             */
/*   Updated: 2023/06/01 15:18:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_utils_1(char **command)
{
	DIR		*dir;

	if (command && ft_strchr(command[0], '/'))
	{
		dir = opendir(command[0]);
		if (dir != NULL)
		{
			ft_putstr_fd(command[0], 2);
			ft_putendl_fd(" is a directory", 2);
			exit(126);
		}
		execve(command[0], command, get__env());
		perror(command[0]);
		exit(127);
	}
}
