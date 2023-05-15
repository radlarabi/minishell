/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:56:03 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/15 22:59:30 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*sub_check_syntax_t1(t_command *t1)
{
	while (t1 && t1->opr != OPER && t1->type != WORD
			&& t1->type != DOUBLE_Q && t1->type != SINGLE_Q
			&& t1->state == GENERAL && t1->type != OTHER)
		t1 = t1->next;
	return t1;
}

t_command	*sub_check_syntax_t2(t_command *t2)
{
	while (t2 && t2->opr != OPER && t2->type != WORD
			&& t2->type != DOUBLE_Q && t2->type != SINGLE_Q
			&& t2->state == GENERAL && t2->type != OTHER)
		t2 = t2->prev;
	return t2;
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
			t1 = sub_check_syntax_t1(tmp->next);
			t2 = sub_check_syntax_t2(tmp->prev);
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
