/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:03:56 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/11 14:19:29 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_cmd_line **commands_v)
{
	t_env	*tmp;

	(void)commands_v;
	tmp = g_gv->env;
	printf("=======>%d\n",tmp->flag);
	while (tmp)
	{
		if (!tmp->flag)
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(tmp->value, 1);
		}
		else if (tmp->flag == 1)
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd("", 1);
		}
		tmp = tmp->next;
	}
	g_gv->env->flag = 0;
	g_gv->exit_status = 0;
	//exit(0);
}
