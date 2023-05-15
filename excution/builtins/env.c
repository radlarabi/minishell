/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:03:56 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/15 17:26:04 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_cmd_line **commands_v)
{
	t_env	*tmp;

	(void)commands_v;
	tmp = g_gv->env;
	while (tmp)
	{
		if (tmp->value && !tmp->flag && tmp->value[0])
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(tmp->value, 1);
		}
		else if (tmp->value && tmp->flag == 1)
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd("", 1);
		}
		tmp = tmp->next;
	}
	g_gv->exit_status = 0;
}
