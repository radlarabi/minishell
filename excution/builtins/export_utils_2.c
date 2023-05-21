/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:49:45 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/21 22:49:55 by hlakhal-         ###   ########.fr       */
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
