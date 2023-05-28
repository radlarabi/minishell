/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:04:47 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/28 01:37:10 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	home_not_set_cd(char *home_dir)
{
	if (!home_dir)
	{
		ft_putendl_fd("cd: HOME not set", 1);
		g_gv->exit_status = 1;
		return (1);
	}
	return (0);
}
