/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:53:41 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/10 21:31:21 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node(t_env **env, char *env_var, char *env_val, int a)
{
	t_env	*new_node;
	char *tab;
	if (env_var)
	{
		new_node = malloc(sizeof(t_env));
		if (!env_val)
		{
			new_node->value = ft_strdup("");
			new_node->var = ft_strdup(env_var);
			if (a)
				new_node->flag = 2;
			else if (!a)
				new_node->flag = 1;
			new_node->next = (*env);
			(*env) = new_node;
		}
		else if (!a)
		{
			new_node->value = env_val;
			new_node->var = env_var;
			new_node->flag = 0;
			new_node->next = (*env);
			(*env) = new_node;
		}
	}
}
char	*remove_char(char *string, char c, int pos)
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
			current->value = new_env_val;
			break ;
		}
		current = current->next;
	}
}

void join_value(t_env **env, char *env_var, char *new_env_val)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, env_var) == 0)
		{
			current->value = ft_strjoin(current->value,new_env_val);
			break ;
		}
		current = current->next;
	}
}

t_env *dup_env(t_env *env_list)
{
	t_env *new_dup;
	if (!env_list)
		return NULL;
	else
	{
		new_dup = malloc(sizeof(t_env));
		new_dup->value = env_list->value;
		new_dup->var = env_list->var;
		new_dup->next = dup_env(env_list->next);
		return new_dup;
	}
}

int	ft_export(t_cmd_line **commands_v)
{
	t_env		*tmp;
	t_cmd_line	*temp;
	char		*value_of_var;
	char		**export_value;
	int			len;
	size_t		i;
	int			j;
	int			flag;
	char *tab;

	flag = 0;
	temp = (*commands_v);
	tmp = dup_env(g_gv->env);
	j = 1;
	i = 0;
	while (temp->cmds[i])
		i++;
	len = i;
	while (j <= len)
	{
		i = 0;
		flag = 0;
		tmp->flag = 0;
		value_of_var = temp->cmds[j];
		while (value_of_var && i < ft_strlen(value_of_var))
		{
			if (!flag && value_of_var[i] == '=' && value_of_var[i - 1] != '+')
			{
				export_value = splitre_whit_pos(value_of_var, i);
				export_value[1] = remove_char(export_value[1], '=', 0);
				flag = 1;
				if (export_value && export_value[0] && export_value[1]
					&& !check_syntax_cmd(export_value[0]))
				{
					if (ft_cherch_node(export_value[0]))
						change_value(&g_gv->env, export_value[0], export_value[1]);
					else
						add_node(&g_gv->env, export_value[0], export_value[1],0);
				}
				else if (check_syntax_cmd(export_value[0]))
				{
					ft_putstr_fd("export: ", 1);
					ft_putstr_fd(value_of_var, 1);
					ft_putendl_fd(" : not a valid identifier", 1);
					g_gv->exit_status = 1;
				}
			}
			else if (!flag && value_of_var[i] == '+' && value_of_var[i
					+ 1] == '=')
			{
				export_value = splitre_whit_pos(value_of_var, i + 1);
				export_value[0] = remove_char(export_value[0], '+', i);
				export_value[1] = remove_char(export_value[1], '=', 0);
				if (export_value && export_value[0] && export_value[1]
					&& !check_syntax_cmd(export_value[0]))
				{
					if (ft_cherch_node(export_value[0]))
						join_value(&g_gv->env, export_value[0], export_value[1]);
					else
						add_node(&g_gv->env, export_value[0], export_value[1],0);
				}
				else if (check_syntax_cmd(export_value[0]))
				{
					ft_putstr_fd("export: ", 1);
					ft_putstr_fd(value_of_var, 1);
					ft_putendl_fd(" : not a valid identifier", 1);
					g_gv->exit_status = 1;
				}
				flag = 1;
			}
			else if (!flag  && (!ft_strchr(value_of_var,'=') && !ft_strchr(value_of_var,'+') ))
			{
				if (check_syntax_cmd(value_of_var))
				{
					ft_putstr_fd("export: ", 1);
					ft_putstr_fd(value_of_var, 1);
					ft_putendl_fd(" : not a valid identifier", 1);
					g_gv->exit_status = 1;
				}
				else
					add_node(&g_gv->env, value_of_var,NULL,1);
				flag = 1;
			}
			i++;
		}
		if (!temp->cmds[j] && len == 1)
		{
			while (tmp)
			{
				if (!ft_strcmp(tmp->value,"") && tmp->flag != 1)
				{
					ft_putstr_fd("declare -x ", 1);
					ft_putendl_fd(tmp->var, 1);
				}
				else
				{
					ft_putstr_fd("declare -x ", 1);
					ft_putstr_fd(tmp->var, 1);
					ft_putstr_fd("=", 1);
					ft_putstr_fd("\"", 1);
					ft_putstr_fd(tmp->value, 1);
					ft_putendl_fd("\"", 1);
				}
				tmp = tmp->next;
			}
			g_gv->exit_status = 0;
		}
		j++;
	}
	return (0);
}
