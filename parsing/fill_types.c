/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:13:29 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/06 14:01:25 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_types1(t_command *tmp, char c, int *i, char *str)
{
	if (c == '-')
	{
		tmp->len = 1;
		tmp->type = DASH;
		tmp->opr = N_OPER;
		(*i)++;
	}
	else if (ft_isalnum(c))
	{
		while (ft_isalnum(str[*i]))
		{
			tmp->len++;
			(*i)++;
		}
		tmp->type = WORD;
	}
	else if (c == ' ')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = SPACE;
		(*i)++;
	}
}
void	fill_types2(t_command *tmp, char c, int *i, char *str)
{
	if (c == '\"')
	{
		tmp->len = 1;
		tmp->type = DOUBLE_Q;
		(*i)++;
	}
	else if (c == '\'')
	{
		tmp->len = 1;
		tmp->type = SINGLE_Q;
		(*i)++;
	}
	else if (c == '<' && str[(*i) + 1] != '<')
	{
		tmp->opr = OPER;
		tmp->len = 1;
		tmp->type = RED_IN;
		(*i)++;
	}
}
void	fill_types3(t_command *tmp, char c, int *i, char *str)
{
	if (c == '>' && str[(*i) + 1] != '>')
	{
		tmp->len = 1;
		tmp->opr = OPER;
		(*i)++;
		tmp->type = RED_OUT;
	}
	else if (c == '>' && str[(*i) + 1] == '>')
	{
		tmp->opr = OPER;
		tmp->len = 2;
		tmp->type = APPE;
		(*i) += 2;
	}
	else if (c == '<' && str[(*i) + 1] == '<')
	{
		tmp->opr = OPER;
		tmp->len = 2;
		tmp->type = HERDOC;
		(*i) += 2;
	}
}
void	fill_types4(t_command *tmp, char c, int *i, char *str)
{
	if (c == '.' && str[(*i) + 1] == '.')
	{
		tmp->len = 2;
		tmp->opr = N_OPER;
		tmp->type = WORD;
		(*i) += 2;
	}
	else if (c == '.' && str[(*i) + 1] != '.')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = WORD;
		(*i) += 1;
	}
	else if (c == '|')
	{
		tmp->opr = OPER;
		tmp->len = 1;
		tmp->type = PIPE;
		(*i)++;
	}
}
void	fill_types5(t_command *tmp, char c, int *i)
{
	if (c == '?')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = QEST;
		(*i)++;
	}
	else if (c == '$')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = ENV;
		(*i)++;
	}
}
void	fill_types(t_command *tmp, char c, int *i, char *str)
{
	if (c == '-' || ft_isalnum(c) || c == ' ')
		fill_types1(tmp, c, i, str);
	else if (c == '\"' || c == '\'' || (c == '<' && str[(*i) + 1] != '<'))
		fill_types2(tmp, c, i, str);
	else if ((c == '>' && str[(*i) + 1] != '>') || (c == '>' && str[(*i)
				+ 1] == '>') || (c == '<' && str[(*i) + 1] == '<'))
		fill_types3(tmp, c, i, str);
	else if ((c == '.' && str[(*i) + 1] == '.') || (c == '.' && str[(*i)
				+ 1] != '.') || c == '|')
		fill_types4(tmp, c, i, str);
	else if (c == '?' || c == '$')
		fill_types5(tmp, c, i);
	else
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = OTHER;
		(*i)++;
	}
}
