/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:53:34 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/18 15:00:56 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	line_cmd(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

int	ft_rep_n(char *line)
{
	int	cont;
	int	len;
	int	i;

	i = 0;
	cont = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == '-' && line[i + 1] == 'n')
		{
			i++;
			while (line[i] && line[i] == 'n')
			{
				cont++;
				i++;
			}
		}
		i++;
	}
	if (len - 1 > 0 && len - 1 == cont)
		return (1);
	return (0);
}

void	ft_echo_utils(char **cmds, int *i, int *flag)
{
	while (cmds[(*i)] && (!ft_strcmp(cmds[(*i)], "-n") || ft_rep_n(cmds[(*i)])))
	{
		(*flag) = 1;
		(*i)++;
	}
	while (cmds[(*i)])
	{
		ft_putstr_fd(cmds[(*i)], 1);
		if (cmds[(*i) + 1] && cmds[(*i)][0] != '\0')
			write(1, " ", 1);
		(*i)++;
	}
}

int	ft_echo(t_cmd_line **commands_v)
{
	int			i;
	int			flag;
	t_cmd_line	*tmp;

	tmp = (*commands_v);
	if (tmp->infile != -1 || tmp->outfile != -1)
	{
		flag = 0;
		i = 1;
		while (i < line_cmd(tmp->cmds))
			ft_echo_utils(tmp->cmds, &i, &flag);
		if (!flag)
			write(1, "\n", 1);
		g_gv->exit_status = 0;
	}
	return (0);
}
