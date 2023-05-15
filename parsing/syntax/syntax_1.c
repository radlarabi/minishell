/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:31:32 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/15 17:36:23 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(void)
{
	printf(ERROR_MSG "\n");
	g_gv->exit_status = 258;
}

int	chech_syntax_exclamation_mark(t_command *tmp)
{
	t_command *t1;

	t1 = tmp->prev;
	while (t1 && (t1->type == SPACE || t1->type == DOUBLE_Q || t1->type == SINGLE_Q))
	{
		if (t1->type == HERDOC && t1->state == GENERAL)
			return 1;
		t1 = t1->prev;
	}
	if (!t1)
	{
		error_msg();
		return (0);
	}
	return 1;
}

int	sub_check_syntax_error(t_command **cmd)
{
	t_command	*tmp;
	t_command	*t1;
	int i;

	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		if (tmp->state == GENERAL && (!ft_strcmp(tmp->content, "&&") 
			|| !ft_strcmp(tmp->content, ";" ) || !ft_strcmp(tmp->content, ")" ) 
			|| !ft_strcmp(tmp->content, "(" ) || !ft_strcmp(tmp->content, "&" ) 
			|| !ft_strcmp(tmp->content, "\\" ) ))
		{
			error_msg();
			return (0);
		}
		else if (!ft_strcmp(tmp->content, "!"))
		{
			if (!chech_syntax_exclamation_mark(tmp))
				return 0;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_syntax_1(t_command *tmp, t_command *t1, t_command *t2)
{
	if (!t1 || (!t2 && tmp && tmp->type == PIPE && tmp->state == GENERAL))
	{
		if (!t2 && tmp && tmp->opr == OPER && tmp->state == GENERAL
			&& tmp->type != OTHER && tmp->type != DOUBLE_Q)
		{
			error_msg();
			return (0);
		}
		if (!t1 && tmp && tmp->opr == OPER && tmp->state == GENERAL)
		{
			error_msg();
			return (0);
		}
		if (!t1 && tmp->type != HERDOC && tmp->type != RED_IN
			&& tmp->type != RED_OUT && tmp->type != APPE )
		{
			error_msg();
			return (0);
		}
	}
	return (1);
}

int	check_syntax_2(t_command *tmp, t_command *t1, t_command *t2)
{
	if (t1->opr == OPER)
	{
		if (t1->type == PIPE && t1->state == GENERAL)
		{
			error_msg();
			return (0);
		}
	}
	if (t2->opr == OPER)
	{
		if ((t2->type == PIPE && tmp && tmp->type == PIPE
				&& t2->state == GENERAL) || (t2->type != PIPE && tmp
				&& tmp->type != PIPE && t2->state == GENERAL) || (tmp
				&& tmp->type == PIPE))
		{
			error_msg();
			return (0);
		}
	}
	return (1);
}