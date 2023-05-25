/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:51:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/25 20:50:27 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sub_check_qotes(char *str, int *i, int a)
{
	int	j;

	j = 0;
	if (str[*i] == a)
	{
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == a)
			{
				j = 1;
				break ;
			}
			(*i)++;
		}
		if (j == 0)
			return (0);
	}
	return (1);
}

int	check_close_qotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!sub_check_qotes(str, &i, 39) || !sub_check_qotes(str, &i, 34))
		{
			error_msg();
			return (0);
		}
		i++;
	}
	return (1);
}

void	extend_cmd(t_command **cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp->state == GENERAL && (tmp->type == RED_IN
				|| tmp->type == RED_OUT || tmp->type == PIPE
				|| tmp->type == HERDOC || tmp->type == APPE))
		{
			ft_lstadd_middle(&tmp);
		}
		tmp = tmp->next;
		i++;
	}
}

char	*ft_getenv(char *str)
{
	t_env	*temp;

	temp = g_gv->env;
	while (temp)
	{
		if (!ft_strcmp(str, temp->var))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	is_quots(char *str, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i] && i != index)
	{
		if (!open && str[i] == '\"')
			open = 2;
		else if (open == 2 && str[i] == '\"')
			open = 0;
		if (!open && str[i] == '\'')
			open = 3;
		else if (open == 3 && str[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}
