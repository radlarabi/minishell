/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:04:47 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/21 22:31:30 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_utils_2(char *path, char *prev_dir, int flag)
{
	if (path && chdir(path) != -1)
	{
		if (flag)
			free(path);
		prev_dir = ft_getenv("OLDPWD");
		change_value(&g_gv->env, "OLDPWD", ft_strdup(prev_dir));
		g_gv->exit_status = 0;
		return (1);
	}
	return (0);
}
