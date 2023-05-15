/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/10 22:36:44 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_env **head_ref, char *key, char *key1)
{
	t_env	*temp;
	t_env	 *prev;

	temp = *head_ref;

	if (temp != NULL && temp->var == key &&  temp->value == key1)
	{
		*head_ref = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && (temp->var != key || temp->value != key1))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp);
}

int	ft_unset(t_cmd_line **commands_v)
{
	t_env	*temp;
	char	*var;

	temp = g_gv->env;
	var = (*commands_v)->cmds[1];
	if (check_syntax_cmd(var))
	{
		ft_putstr_fd("unset: ", 1);
		ft_putstr_fd(var, 1);
		ft_putendl_fd(" : not a valid identifier", 1);
		g_gv->exit_status = 1;
	}
	while (temp)
	{
		if (!ft_strcmp(temp->var,var))
		{
			remove_node(&g_gv->env,temp->var,temp->value);
			break ;
		}
		temp = temp->next;
	}
	g_gv->exit_status = 0;
	return (0);
}
