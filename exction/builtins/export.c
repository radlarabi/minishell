/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:53:41 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/09 13:07:03 by rlarabi          ###   ########.fr       */
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
	int		i;
	size_t	cont;

	cont = 0;
	i = 0;
	if (ft_strchr("0123456789", cmd[0]))
		return (1);
	while (cmd && cmd[i])
	{
		if (ft_strchr("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_",
						cmd[i]))
			cont += 1;
		if (ft_strlen(cmd) == cont)
			return (0);
		i++;
	}
	return (1);
}

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
}
char	**splitre_whit_pos(char *str, size_t pos)
{
	size_t	length;
	char	**result;

	result = malloc(2 * sizeof(char *));
	length = ft_strlen(str);
	if (str[pos] == '=')
	{
		if (pos >= 0 && pos < length)
		{
			result[0] = malloc((pos + 1) * sizeof(char));
			ft_strncpy(result[0], str, pos);
			result[0][pos] = '\0';
			result[1] = malloc((length - pos + 1) * sizeof(char));
			ft_strncpy(result[1], str + pos, length - pos);
			result[1][length - pos] = '\0';
		}
		else
		{
			result[0] = ft_strdup(str);
			result[1] = NULL;
		}
	}
	return (result);
}

int	ft_cherch_node(char *exp_var)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = g_gv->env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, exp_var))
			return (1);
		temp = temp->next;
	}
	return (0);
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

	flag = 0;
	temp = (*commands_v);
	tmp = g_gv->env;
	j = 1;
	i = 0;
	while (temp->cmds[i])
		i++;
	len = i;
	while (j <= len)
	{
		i = 0;
		flag = 0;
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
						add_node(&g_gv->env, export_value[0], export_value[1]);
				}
				else if (check_syntax_cmd(export_value[0]))
				{
					ft_putstr_fd("export: ", 2);
					ft_putstr_fd(value_of_var, 2);
					ft_putendl_fd(" : not a valid identifier", 2);
					exit(1);
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
						add_node(&g_gv->env, export_value[0], export_value[1]);
				}
				else if (check_syntax_cmd(export_value[0]))
				{
					ft_putstr_fd("export: ", 2);
					ft_putstr_fd(value_of_var, 2);
					ft_putendl_fd(" : not a valid identifier", 2);
					exit(1);
				}
				flag = 1;
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
			exit(0);
		}
		j++;
	}
	exit(0);
	return (0);
}
