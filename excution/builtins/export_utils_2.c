/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:49:45 by rlarabi           #+#    #+#             */
/*   Updated: 2023/06/03 22:35:56 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_value(t_env **env, char *env_var, char *new_env_val)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, env_var) == 0)
		{
			current->flag = 0;
			current->value = ft_strjoin(current->value, new_env_val);
			break ;
		}
		current = current->next;
	}
}

void	ft_export_utils_1(t_cmd_line **commands_v, int len)
{
	size_t	i;
	int		j;
	int		flag;
	char	*value_of_var;

	j = 1;
	while (j <= len)
	{
		i = 0;
		flag = 0;
		value_of_var = (*commands_v)->cmds[j];
		if (value_of_var && !value_of_var[0])
			error_identifie(value_of_var);
		while (value_of_var && i < ft_strlen(value_of_var))
		{
			export_utils4(value_of_var, i, &flag,
				ft_len_tab((*commands_v)->cmds, &len));
			i++;
		}
		if (!(*commands_v)->cmds[j] && len == 1)
			display_export(*(ft_len_tab((*commands_v)->cmds, &len)));
		j++;
	}
}

t_env	*merge_lists(t_env *left, t_env *right)
{
	t_env	dummy;
	t_env	*tail;

	tail = &dummy;
	dummy.next = NULL;
	while (left != NULL && right != NULL)
	{
		if (ft_strcmp(left->var, right->var) < 0)
		{
			tail->next = left;
			left = left->next;
		}
		else
		{
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}
	if (left != NULL)
		tail->next = left;
	else
		tail->next = right;
	return (dummy.next);
}

t_env	*sort_list(t_env *lst)
{
	t_env	*slow;
	t_env	*fast;
	t_env	*second_half;
	t_env	*left;
	t_env	*right;

	if (lst == NULL || lst->next == NULL)
		return (lst);
	slow = lst;
	fast = lst->next;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	second_half = slow->next;
	slow->next = NULL;
	left = sort_list(lst);
	right = sort_list(second_half);
	return (merge_lists(left, right));
}
