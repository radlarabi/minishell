/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:31:40 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/20 22:59:30 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extand_var(char *cmds)
{
	int		j;
	char	*ret;

	j = 0;
	ret = NULL;
	if (cmds && (cmds[0] == '$') && ft_strlen(cmds) == 1)
	{
		ret = ft_strjoin(ret, "$");
		return (ret);
	}
	while (cmds[j])
	{
		if (cmds[j] == '\"')
			extand_var_in_double_qoutes(&ret, cmds, &j);
		else if (cmds[j] == '\'')
			ignore_extand_in_single_quotes(&ret, cmds, &j);
		else
		{
			if (sub_extand_var(&ret, cmds, &j))
				break ;
		}
	}
	return (ret);
}

char	**change_content_cmds(char **cmds, int leen)
{
	int		j;
	char	**ret;

	ret = malloc(sizeof(char *) * (leen + 1));
	if (!ret)
		return (NULL);
	j = 0;
	change_content_cmds_utils(ret, cmds, &j, leen);
	ret[j] = 0;
	free_2d_table(cmds);
	return (ret);
}

void	remove_double_quotes(char *str, char **ret, int *i, int *j)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != '\"')
	{
		(*ret)[(*j)] = str[(*i)];
		(*j)++;
		(*i)++;
	}
	if (str[(*i)] == '\"')
		(*i)++;
}

void	remove_single_quotes(char *str, char **ret, int *i, int *j)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != '\'')
	{
		(*ret)[(*j)] = str[(*i)];
		(*j)++;
		(*i)++;
	}
	if (str[(*i)] == '\'')
		(*i)++;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	if (!str)
		return (NULL);
	ret = malloc(ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			remove_double_quotes(str, &ret, &i, &j);
		else if (str[i] == '\'')
			remove_single_quotes(str, &ret, &i, &j);
		else
			ret[j++] = str[i++];
	}
	ret[j] = 0;
	free(str);
	return (ret);
}
