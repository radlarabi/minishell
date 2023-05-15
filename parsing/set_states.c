/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_states.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:42:01 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/15 17:55:17 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_states_in_double_q(t_command **tmp)
{
	int	count;

	count = 0;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->type != DOUBLE_Q)
	{
		count++;
		(*tmp) = (*tmp)->next;
	}
	if (!(*tmp))
		return (1);
	while (count)
	{
		(*tmp) = (*tmp)->prev;
		count--;
	}
	while ((*tmp) && (*tmp)->type != DOUBLE_Q)
	{
		(*tmp)->state = IN_DC;
		(*tmp) = (*tmp)->next;
	}
	(*tmp)->state = GENERAL;
	(*tmp) = (*tmp)->next;
	return (0);
}
int	set_states_in_single_q(t_command **tmp)
{
	int	count;

	count = 0;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->type != SINGLE_Q)
	{
		count++;
		(*tmp) = (*tmp)->next;
	}
	if (!(*tmp))
		return (1);
	while (count)
	{
		(*tmp) = (*tmp)->prev;
		count--;
	}
	while ((*tmp) && (*tmp)->type != SINGLE_Q)
	{
		(*tmp)->state = IN_SC;
		(*tmp) = (*tmp)->next;
	}
	(*tmp)->state = GENERAL;
	(*tmp) = (*tmp)->next;
	return (0);
}
void	set_states(t_command **cmd)
{
	t_command *tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		tmp->state = GENERAL;
		if (tmp->type == DOUBLE_Q)
		{
			if (set_states_in_double_q(&tmp))
				return ;
		}
		else if (tmp->type == SINGLE_Q)
		{
			if (set_states_in_single_q(&tmp))
				return ;
		}
		else
			tmp = tmp->next;
	}
}
char	*struct_to_str(t_command **cmd)
{
	t_command	*tmp;
	char		*str;

	tmp = *cmd;
	str = NULL;
	while (tmp != NULL)
	{
		str = ft_strjoin(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

char	*search_path(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], "PATH", 4))
			return (ev[i]);
		i++;
	}
	return (NULL);
}
