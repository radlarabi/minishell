/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/24 19:02:25 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*duplicate_linked_list(t_env *head)
{
	t_env	*new_head;
	t_env	*current_original;
	t_env	*current_duplicate;
	t_env	*new_node;

	if (head == NULL)
	{
		return (NULL);
	}
	new_head = (t_env *)malloc(sizeof(t_env));
	new_head->var = ft_strdup(head->var);
	new_head->value = ft_strdup(head->value);
	new_head->flag = 0;
	new_head->next = NULL;
	current_original = head->next;
	current_duplicate = new_head;
	while (current_original != NULL)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		new_node->var = ft_strdup(current_original->var);
		new_node->value = ft_strdup(current_original->value);
		new_node->flag = 0;
		new_node->next = NULL;
		current_duplicate->next = new_node;
		current_original = current_original->next;
		current_duplicate = current_duplicate->next;
	}
	return (new_head);
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
			|| ft_strcmp(temp->value, key1)))
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
	t_env	*tmp;
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
		temp = duplicate_linked_list(g_gv->env);
		while (temp)
		{
			tmp = temp->next;
			if (var && !ft_strcmp(temp->var, var))
				remove_node(&g_gv->env, temp->var, temp->value);
			free(temp->var);
			free(temp->value);
			free(temp);
			temp = tmp;
		}
	}
	return (0);
}
