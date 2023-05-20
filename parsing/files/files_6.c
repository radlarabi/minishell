/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:03:19 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/20 22:57:02 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sub_command_struct(t_cmd_line **tmp)
{
	int		j;
	char	*t_mp;

	j = 0;
	while ((*tmp)->cmds && (*tmp)->cmds[j])
	{
		if (!ft_strcmp((*tmp)->cmds[j], "\"\"") || !ft_strcmp((*tmp)->cmds[j],
				"\'\'"))
		{
			t_mp = (*tmp)->cmds[j];
			(*tmp)->cmds[j++] = ft_strdup("");
			free(t_mp);
		}
		else if (!ft_strcmp((*tmp)->cmds[j], "<<"))
			j += 2;
		else if (!ft_strcmp((*tmp)->cmds[j], "<"))
			j += 2;
		else if (!ft_strcmp((*tmp)->cmds[j], ">"))
			j += 2;
		else if (!ft_strcmp((*tmp)->cmds[j], ">>"))
			j += 2;
		else
			extand_in_comamnd_struct(tmp, &j);
	}
	return (j);
}

char	**fill_temp_of_command_struct(char **cmds)
{
	char	**temp;
	int		j;

	j = 0;
	while (cmds && cmds[j])
		j++;
	temp = malloc((j + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	j = 0;
	while (cmds && cmds[j])
	{
		temp[j] = ft_strdup(cmds[j]);
		j++;
	}
	temp[j] = 0;
	return (temp);
}

t_cmd_line	*init_temp_cmd_line(char **cmds, int i)
{
	char		*t_mp;
	t_cmd_line	*tmp;

	tmp = NULL;
	tmp = lst_init_cmds();
	t_mp = cmds[i];
	cmds[i] = set_spliter(cmds[i], ' ');
	free(t_mp);
	tmp->cmds = ft_split(cmds[i], -1);
	free(cmds[i]);
	return (tmp);
}

int	strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	change_content_cmds_utils(char **ret, char **cmds, int *j, int leen)
{
	int	i;

	i = 0;
	while (leen > i)
	{
		if (leen > i && ((!ft_strcmp(cmds[i], "<") || !ft_strcmp(cmds[i], "<<")
					|| !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>")))
			&& !cmds[i + 1])
		{
			ret[*j] = ft_strdup(cmds[0]);
			(*j)++;
		}
		while (leen > i && (!ft_strcmp(cmds[i], "<") || !ft_strcmp(cmds[i],
					"<<") || !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i],
					">>")))
			i += 2;
		if (leen > i && cmds[i])
		{
			ret[*j] = ft_strdup(cmds[i]);
			(*j)++;
		}
		i++;
	}
}
