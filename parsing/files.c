/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/06/03 21:28:11 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_files_in_command_struct(char **temp, t_cmd_line **tmp)
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
}

char	**change_content(t_cmd_line **cmd, int len)
{
	int		i;
	int		k;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	k = 0;
	while (i < len)
	{
		if ((*cmd)->cmds_exe && (*cmd)->cmds_exe[i])
		{
			ret[k] = ft_strdup((*cmd)->cmds_exe[i]);
			k++;
		}
		i++;
	}
	ret[k] = 0;
	free_2d_table((*cmd)->cmds);
	return (ret);
}

void	change_commands_struct(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;
	char		**temp;
	int			p;
	int			len;

	p = 0;
	tmp = *cmd;
	len = 0;
	while (tmp)
	{
		if (p != 0)
			g_gv->exit_status = 0;
		temp = fill_temp_of_command_struct(tmp->cmds);
		tmp->cmds_exe = alloc_cmd_exe(temp);
		open_files_in_command_struct(temp, &tmp);
		len = sub_command_struct(&tmp);
		tmp->cmds = change_content(&tmp, len);
		if (temp)
			free(temp);
		tmp = tmp->next;
		p++;
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
