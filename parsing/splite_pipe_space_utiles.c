/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe_space_utiles.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:22:42 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/15 23:23:43 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_set_spliter(char *str, int *i, int a, char **s)
{
	while (str[(*i)])
	{
		(*s)[(*i)] = str[(*i)];
		i++;
		if (str[(*i)] == a)
		{
			(*s)[(*i)] = str[(*i)];
			(*i)++;
			return 1;
		}
	}
	return 0;
}
int	sub_set_spliter_2(char *str, int *i, char **s)
{
	if (str[(*i)] == 39)
	{
		if (skip_set_spliter(str, i, 39, s))
			return 1;
	}
	else if (str[(*i)] == 34)
	{
		if (skip_set_spliter(str, i, 34, s))
			return 1;
	}
	return 0;
}

int	sub_set_spiter_1(char *str, int *i, char **s, int c)
{
	if (str[(*i)] == 39 || str[(*i)] == 34)
	{
		if (sub_set_spliter_2(str, i, s))
			return 1;
	}
	else if (str[(*i)] == c)
	{
		(*s)[(*i)] = -1;
		(*i)++;
	}
	else
	{
		(*s)[(*i)] = str[(*i)];
		(*i)++;
	}
	return 0;
}

char	*set_spliter(char *str, char c)
{
	char	*s;
	int		i;

	if (!str)
		return (NULL);
	s = malloc(ft_strlen(str) + 1);
	if (!s)
		return NULL;
	i = 0;
	while (str[i])
	{
		if (sub_set_spiter_1(str, &i, &s, c))
			break;
	}
	s[i] = 0;
	return (s);
}