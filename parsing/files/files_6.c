/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:03:19 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/26 18:52:39 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sub_command_struct(t_cmd_line **tmp)
{
	int		j;
	int		len;
	char	*t_mp;

	j = 0;
	len = 0;
	while ((*tmp)->cmds_exe && (*tmp)->cmds_exe[len])
		len++;
	while ((*tmp)->cmds_exe && (*tmp)->cmds_exe[j])
	{
		if (!ft_strcmp((*tmp)->cmds_exe[j], "\"\"")
			|| !ft_strcmp((*tmp)->cmds_exe[j], "\'\'"))
		{
			t_mp = (*tmp)->cmds_exe[j];
			(*tmp)->cmds_exe[j++] = ft_strdup("");
			free(t_mp);
		}
		else
		{
			extand_in_comamnd_struct(tmp, &j);
			if (len <= j)
				break ;
		}
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
