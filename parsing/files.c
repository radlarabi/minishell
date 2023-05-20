/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/20 19:03:31 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_herdoc(char **temp, t_cmd_line **tmp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		if (!ft_strcmp(temp[j], "<<"))
		{
			if (open_appnd_herdoc(temp, tmp, &j))
				return (1);
		}
		else
			j++;
	}
	return (0);
}

int	open_files_in_command_struct(char **temp, t_cmd_line **tmp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		if (!ft_strcmp(temp[j], ">>"))
		{
			if (open_appnd_herdoc(temp, tmp, &j))
				break ;
		}
		else if (!ft_strcmp(temp[j], "<") || !ft_strcmp(temp[j], ">"))
		{
			if (open_read_out_in(temp, tmp, &j))
				break ;
		}
		else
		{
			free(temp[j]);
			j++;
		}
	}
	return (0);
}

void	change_commands_struct(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;
	char		**temp;
	int			j;
	int			i;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		temp = fill_temp_of_command_struct(tmp->cmds);
		j = sub_command_struct(&tmp);
		if (tmp->cmds)
			tmp->cmds = change_content_cmds(tmp->cmds, j);
		if (open_files_in_command_struct(temp, &tmp))
			break ;
		if (temp)
			free(temp);
		tmp = tmp->next;
		i++;
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
			return (NULL);
		free_2d_table(temp);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
	}
	change_commands_struct(&cmd_l);
	return (cmd_l);
}
