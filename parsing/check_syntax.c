/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:56:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/04/14 18:16:43 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_msg(void)
{
	printf(ERROR_MSG "\n");
}

static int	sub_check_syntax_error(t_command **cmd)
{
	t_command	*tmp;
	t_command	*t1;
	int i;
	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		if (tmp->state == GENERAL && (!ft_strncmp(tmp->content, "&&",
					ft_strlen(tmp->content)) || !ft_strncmp(tmp->content, ";",
					ft_strlen(tmp->content)) || !ft_strncmp(tmp->content, ")",
					ft_strlen(tmp->content)) || !ft_strncmp(tmp->content, "(",
					ft_strlen(tmp->content)) || !ft_strncmp(tmp->content, "&",
					ft_strlen(tmp->content)) || !ft_strncmp(tmp->content, "\\",
					ft_strlen(tmp->content))))
		{
			error_msg();
			return (0);
		}
		else if (!ft_strcmp(tmp->content, "*"))
		{
			t1 = tmp->prev;
			while (t1->type == SPACE || t1->type == DOUBLE_Q || t1->type == SINGLE_Q)
			{
				if (t1->type == HERDOC && t1->state == GENERAL)
					return 1;
				t1 = t1->prev;
			}
			if (t1 && t1->type != HERDOC)
			{
				error_msg();
				return (0);
			}
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
			&& tmp->type != RED_OUT && tmp->type != APPE && tmp->type != ENV)
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

int	check_syntax(t_command **cmd)
{
	t_command	*tmp;
	t_command	*t1;
	t_command	*t2;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp && tmp->opr == OPER && tmp->state == GENERAL)
		{
			t1 = tmp->next;
			t2 = tmp->prev;
			while (t1 && t1->opr != OPER && t1->type != WORD
				&& t1->type != DOUBLE_Q && t1->type != SINGLE_Q
				&& t1->state == GENERAL && t1->type != OTHER)
				t1 = t1->next;
			while (t2 && t2->opr != OPER && t2->type != WORD
				&& t2->type != DOUBLE_Q && t2->type != SINGLE_Q
				&& t2->state == GENERAL && t2->type != OTHER)
				t2 = t2->prev;
			if (!t1 || !t2)
			{
				if (!check_syntax_1(tmp, t1, t2))
					return (0);
			}
			else if (!check_syntax_2(tmp, t1, t2))
					return (0);
		}
		tmp = tmp->next;
	}
	if (!sub_check_syntax_error(cmd))
		return (0);
	return (1);
}
