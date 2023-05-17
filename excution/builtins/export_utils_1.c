/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:17:27 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/17 13:51:51 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*dup_env(t_env *env_list)
{
	t_env	*new_dup;

	if (!env_list)
		return (NULL);
	else
	{
		new_dup = malloc(sizeof(t_env));
		if (!new_dup)
			return (NULL);
		new_dup->value = env_list->value;
		new_dup->var = env_list->var;
		new_dup->next = dup_env(env_list->next);
		return (new_dup);
	}
}

void	error_identifie(char *value_of_var)
{
	ft_putstr_fd("export: ", 1);
	ft_putstr_fd(value_of_var, 1);
	ft_putendl_fd(" : not a valid identifier", 1);
	g_gv->exit_status = 1;
}

void	export_utils1(char *value_of_var, int *flag)
{
	ft_putstr_fd("export: ", 1);
	ft_putstr_fd(value_of_var, 1);
	ft_putendl_fd(" : not a valid identifier", 1);
	*flag = 1;
	g_gv->exit_status = 1;
}

void	export_utils2(char *value_of_var, int i, int *flag, int *flag1)
{
	char	**export_value;

	export_value = splitre_whit_pos(value_of_var, i);
	export_value[1] = remove_char(export_value[1], 0);
	*flag = 1;
	if (export_value && export_value[0] && export_value[1]
		&& !check_syntax_cmd(export_value[0]))
	{
		if (ft_cherch_node(export_value[0]))
		{
			change_value(&g_gv->env, export_value[0], export_value[1]);
			(free(export_value[1]), free(export_value[0]));
			*flag1 = 0;
		}
		else
		{
			add_node(&g_gv->env, export_value[0], export_value[1], 0);
			(free(export_value[1]), free(export_value[0]));
			*flag1 = 0;
		}
	}
	else if (check_syntax_cmd(export_value[0]))
		error_identifie(value_of_var);
	free(export_value);
}

void	export_utils3(char *value_of_var, int i, int *flag, int *flag1)
{
	char	**export_value;

	export_value = splitre_whit_pos(value_of_var, i + 1);
	export_value[0] = remove_char(export_value[0], i);
	export_value[1] = remove_char(export_value[1], 0);
	if (export_value && export_value[0] && export_value[1]
		&& !check_syntax_cmd(export_value[0]))
	{
		if (ft_cherch_node(export_value[0]))
		{
			join_value(&g_gv->env, export_value[0], export_value[1]);
			(free(export_value[1]), free(export_value[0]));
			*flag1 = 0;
		}
		else
		{
			add_node(&g_gv->env, export_value[0], export_value[1], 0);
			(free(export_value[1]), free(export_value[0]));
			*flag1 = 0;
		}
	}
	else if (check_syntax_cmd(export_value[0]))
		error_identifie(value_of_var);
	*flag = 1;
	free(export_value);
}
