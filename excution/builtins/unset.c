/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/21 19:55:21 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_env **head_ref, char *key, char *key1)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head_ref;
	if (temp != NULL && temp->var == key && temp->value == key1)
	{
		*head_ref = temp->next;
		free(temp->value);
		free(temp->var);
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
	free(temp->value);
	free(temp->var);
	free(temp);
}

int	ft_unset(t_cmd_line **commands_v)
{
	t_env	*temp;
	char	*var;
	int		i;

	i = 0;
	g_gv->exit_status = 0;
	while ((*commands_v)->cmds && (*commands_v)->cmds[++i])
	{
		var = (*commands_v)->cmds[i];
		if (var && (check_syntax_cmd(var) || !var[0]))
		{
			ft_putstr_fd("unset: ", 1);
			ft_putstr_fd(var, 1);
			ft_putendl_fd(" : not a valid identifier", 1);
			g_gv->exit_status = 1;
		}
		temp = g_gv->env;
		while (temp)
		{
			if (var && !ft_strcmp(temp->var, var))
				remove_node(&g_gv->env, temp->var, temp->value);
			temp = temp->next;
		}
	}
	return (0);
}
