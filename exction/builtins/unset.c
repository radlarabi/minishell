/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/09 15:50:29 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void remove_node(t_env *env)
// {

// }

int ft_unset(t_cmd_line **commands_v)
{
	t_env *temp;
	temp = g_gv->env;
	char *var;
	var = (*commands_v)->cmds[1];
	while(temp)
	{
		if(ft_cherch_node(var))
			printf("fdfdf\n");
		temp = temp->next;
	}
	return 0;
}
