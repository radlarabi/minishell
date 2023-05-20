/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:46:46 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/20 18:51:23 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	sub_add_node(t_env **env, t_env **new_node, \
			char *env_var, char *env_val)
{
	t_env	*temp;

	(*new_node)->value = ft_strdup(env_val);
	(*new_node)->var = ft_strdup(env_var);
	(*new_node)->flag = 0;
	(*new_node)->next = NULL;
	temp = ft_lstlast(*env);
	temp->next = (*new_node);
}

void	add_node(t_env **env, char *env_var, char *env_val, int a)
{
	t_env	*new_node;
	t_env	*temp;

	if (env_var)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		if (!env_val)
		{
			new_node->value = ft_strdup("");
			new_node->var = ft_strdup(env_var);
			if (a)
				new_node->flag = 2;
			else if (!a)
				new_node->flag = 1;
			new_node->next = NULL;
			temp = ft_lstlast(*env);
			temp->next = new_node;
		}
		else if (!a)
			sub_add_node(env, &new_node, env_var, env_val);
	}
}

char	*remove_char(char *string, int pos)
{
	int	length;
	int	i;

	i = pos;
	length = ft_strlen(string);
	if (pos < 0 || pos >= length)
		return (string);
	while (i < length - 1)
	{
		string[i] = string[i + 1];
		i++;
	}
	string[length - 1] = '\0';
	return (string);
}

void	change_value(t_env **env, char *env_var, char *new_env_val)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, env_var) == 0)
		{
			if (new_env_val && !new_env_val[0])
				g_gv->env->flag = 1;
			else
				g_gv->env->flag = 0;
			if (current->value)
				free(current->value);
			if (new_env_val)
			{
				current->value = ft_strdup(new_env_val);
				free(new_env_val);
			}
			else
				current->value = NULL;
			break ;
		}
		current = current->next;
	}
}
