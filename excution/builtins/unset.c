/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/25 23:38:38 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*duplicate_linked_list(t_env *head)
{
	t_env	*new_node;

	new_node = NULL;
	if (head == NULL)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->var = ft_strdup(head->var);
	new_node->value = ft_strdup(head->value);
	new_node->flag = head->flag;
	new_node->next = NULL;
	new_node->next = duplicate_linked_list(head->next);
	return (new_node);
}

void	remove_node(t_env **head_ref, char *key, char *key1)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head_ref;
	if (temp != NULL && !ft_strcmp(temp->var, key)
		&& !ft_strcmp(temp->value, key1))
	{
		*head_ref = temp->next;
		free(temp->value);
		free(temp->var);
		free(temp);
		return ;
	}
	while (temp != NULL && (ft_strcmp(temp->var, key)
			|| (temp->value && ft_strcmp(temp->value, key1))))
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

void	ft_unset_utils(char *var)
{
	if (var && (check_syntax_cmd(var) || !var[0]))
	{
		ft_putstr_fd("unset: ", 1);
		ft_putstr_fd(var, 1);
		ft_putendl_fd(" : not a valid identifier", 1);
		g_gv->exit_status = 1;
	}
}

int	ft_unset(t_cmd_line **commands_v)
{
	t_env	*temp;
	t_env	*tmp;
	char	*var;
	int		i;

	i = 0;
	g_gv->exit_status = 0;
	while ((*commands_v)->cmds && (*commands_v)->cmds[++i])
	{
		var = (*commands_v)->cmds[i];
		ft_unset_utils(var);
		temp = duplicate_linked_list(g_gv->env);
		while (temp)
		{
			tmp = temp->next;
			if (var && !ft_strcmp(temp->var, var))
				remove_node(&g_gv->env, temp->var, temp->value);
			(free(temp->var), free(temp->value), free(temp));
			temp = tmp;
		}
	}
	return (0);
}
