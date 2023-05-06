/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:53:41 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/06 13:51:45 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node(t_env **env, char *env_var, char *env_val)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->value = env_val;
	new_node->var = env_var;
	new_node->next = (*env);
	(*env) = new_node;
}

int	check_class(char *name_of_varaibl)
{
	int	i;

	i = 0;
	while (name_of_varaibl[i])
	{
		i++;
	}
	return (1);
}
int	check_syntax_cmd(char *cmd)
{
	int	i;
	int	cont;

	cont = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (ft_strchr("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_",
				cmd[i]))
		{
			cont += 1;
		}
		if (ft_strlen(cmd) == cont)
			return (0);
		i++;
	}
	return (1);
}
int	ft_export(t_cmd_line **commands_v)
{
	t_env		*tmp;
	t_cmd_line	*temp;
	char		*value_of_var;
	char		**export_value;
	int			len;
	int			i;
	int			j;
	int			flag;

	temp = (*commands_v);
	tmp = g_gv->env;
	flag = 0;
	j = 1;
	i = 0;
	while (temp->cmds[i])
		i++;
	len = i;
	while (j <= len)
	{
		i = 0;
		value_of_var = temp->cmds[j];
		while (value_of_var && i < ft_strlen(value_of_var))
		{
			if (value_of_var[i] == '=')
			{
				export_value = ft_split(value_of_var, '=');
				if (export_value && export_value[0] && export_value[1]
					&& !check_syntax_cmd(export_value[0]))
					add_node(&g_gv->env, export_value[0], export_value[1]);
				else if (check_syntax_cmd(export_value[0]))
				{
					flag = 0;
					ft_putstr_fd("export: ", 2);
					ft_putstr_fd(value_of_var, 2);
					ft_putendl_fd(" : not a valid identifier", 2);
					exit(1);
				}
			}
			else if (!ft_strchr(value_of_var, '=')
					&& check_syntax_cmd(value_of_var))
			{
				flag = 1;
				ft_putstr_fd("export: ", 2);
				ft_putstr_fd(value_of_var, 2);
				ft_putendl_fd(" : not a valid identifier", 2);
				exit(1);
			}
			i++;
		}
		if (!temp->cmds[j] && len == 1)
		{
			while (tmp)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->var, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putendl_fd("\"", 1);
				tmp = tmp->next;
			}
		}
		j++;
	}
	return (0);
}
