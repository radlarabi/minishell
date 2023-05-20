/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utiles_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:49:45 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/20 18:50:57 by rlarabi          ###   ########.fr       */
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
