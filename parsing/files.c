/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/25 20:56:14 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files_in_command_struct(char **temp, t_cmd_line **tmp)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (temp[j])
	{
		if (!ft_strcmp(temp[j], ">>") || !ft_strcmp(temp[j], "<")
			|| !ft_strcmp(temp[j], ">") || !ft_strcmp(temp[j], "<<"))
		{
			if (sub_open_files(temp, tmp, &j))
			{
				while (temp[j])
					free(temp[j++]);
				break ;
			}
		}
		else
			fill_cmds_exe(tmp, temp, &j, &k);
	}
	(*tmp)->cmds_exe[k] = 0;
	return (0);
}

char	**change_content(t_cmd_line **cmd)
{
	int		i;
	char	**ret;

	i = 0;
	while ((*cmd)->cmds_exe && (*cmd)->cmds_exe[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*cmd)->cmds_exe && (*cmd)->cmds_exe[i])
	{
		ret[i] = ft_strdup((*cmd)->cmds_exe[i]);
		i++;
	}
	ret[i] = 0;
	free_2d_table((*cmd)->cmds);
	return (ret);
}

void	change_commands_struct(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;
	char		**temp;
	int			j;
	int			k;

	tmp = *cmd;
	while (tmp)
	{
		temp = fill_temp_of_command_struct(tmp->cmds);
		j = 0;
		k = 0;
		while (temp && temp[j])
			j++;
		tmp->cmds_exe = malloc((j + 1) * sizeof(char *));
		if (!tmp->cmds_exe)
			return ;
		if (open_files_in_command_struct(temp, &tmp))
			break ;
		j = sub_command_struct(&tmp);
		tmp->cmds = change_content(&tmp);
		if (temp)
			free(temp);
		tmp = tmp->next;
	}
}

int	open_herdocs(t_cmd_line **tmp, char **temp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		if (!ft_strcmp(temp[j], "<<"))
		{
			j++;
			files_here_doc(temp, tmp, &j);
			if (g_gv->exit_status == 1)
				return (1);
		}
		else
			j++;
	}
	return (0);
}

t_cmd_line	*commands_struct(char **cmds)
{
	t_cmd_line	*cmd_l;
	t_cmd_line	*tmp;
	int			i;
	char		**temp;

	cmd_l = NULL;
	i = 0;
	while (cmds[i])
	{
		tmp = init_temp_cmd_line(cmds, i);
		temp = fill_temp_of_command_struct(tmp->cmds);
		if (open_herdocs(&tmp, temp))
		{
			free_2d_table(temp);
			free_t_cmd_line(&tmp);
			while (cmds[++i])
				free(cmds[i]);
			return (NULL);
		}
		free_2d_table(temp);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
	}
	change_commands_struct(&cmd_l);
	return (cmd_l);
}
