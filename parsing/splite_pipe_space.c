/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:02:19 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/08 19:02:43 by rlarabi          ###   ########.fr       */
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
		{
			while (str[i])
			{
				s[i] = str[i];
				i++;
				if (str[i] == 39)
					break ;
			}
		}
		else if (str[i] == 34)
		{
			while (str[i])
			{
				s[i] = str[i];
				i++;
				if (str[i] == 34)
                {
                    s[i] = str[i];
				    i++;
					break ;
                }
			}
		}
		else if (str[i] == c)
		{
			s[i] = -1;
		    i++;
		}
		else
		{
			s[i] = str[i];
		    i++;
		}
	}
	s[i] = 0;
	return (s);
}

char	**splite_with_pipes(t_command **cmd)
{
	t_command	*tmp;
	char		*str;
	char		*a;
	char **temp;

	tmp = *cmd;
	extend_cmd(&tmp);
	str = struct_to_str(&tmp);
	a = set_spliter(str, '|');
	temp = ft_split(a, -1);
	if (str)
		free(str);
	if (a)
		free(a);
	return (temp);
}

char	**splite_with_space(char *str)
{
	char **temp;
	char *tmp;

	tmp = set_spliter(str, ' ');
	temp = ft_split(tmp, -1);
	return (temp);
}
