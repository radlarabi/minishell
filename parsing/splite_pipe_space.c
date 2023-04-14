/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:02:19 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/14 18:29:56 by rlarabi          ###   ########.fr       */
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
	// printf("str->%s\n", str);
	while (str[i])
	{
		if (str[i] == 39)
		{
			while (str[i])
			{
				// printf("%c+___%d\n", str[i], i);
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
				// printf("%c-___%d\n", str[i], i);
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
			// printf("c_%c__%d\n", str[i], i);
			s[i] = -1;
		    i++;
		}
		else
		{
			// printf("else_%c__%d\n",str[i], i);
			s[i] = str[i];
		    i++;
		}
	}
	s[i] = 0;
	// printf("----%s----\n\n\n\n\n",s);
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
	// free(str);
	temp = ft_split(a, -1);
	// free(a);
	return (temp);
}

char	**splite_with_space(char *str)
{
	char **temp;
	char *tmp;

	tmp = set_spliter(str, ' ');
	// free(str);
	temp = ft_split(tmp, -1);
	// free(tmp);
	return (temp);
}
