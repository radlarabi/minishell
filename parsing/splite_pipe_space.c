/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:02:19 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/10 22:39:17 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_and_fill_in_quotes(char *str, char **s, int a, int *i)
{
	(*s)[*i] = str[*i];
	(*i)++;
	while (str[*i])
	{
		(*s)[*i] = str[*i];
		if (str[*i] == a)
			break ;
		(*i)++;
	}
}

void	skip_in_quotes(char *str, int a, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == a)
			break ;
		(*i)++;
	}
}

char	*set_spliter(char *str, char c)
{
	char	*s;
	int		i;

	if (!str)
		return (NULL);
	s = malloc(ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			skip_and_fill_in_quotes(str, &s, 39, &i);
		else if (str[i] == 34)
			skip_and_fill_in_quotes(str, &s, 34, &i);
		else if (str[i] == c)
			s[i] = -1;
		else
			s[i] = str[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

char	**splite_with_pipes(t_command **cmd)
{
	t_command	*tmp;
	char		*str;
	char		*a;
	tmp = *cmd;
	extend_cmd(&tmp);
	str = struct_to_str(&tmp);
	a = set_spliter(str, '|');
	free(str);
	return (ft_split(a, -1));
}

char	**splite_with_space(char *str)
{
	return (ft_split(set_spliter(str, ' '), -1));
}
