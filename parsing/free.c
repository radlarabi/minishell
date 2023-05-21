/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:44:24 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/21 16:30:27 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_table(char **temp)
{
	int	i;

	i = 0;
	while (temp && temp[i])
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
}

void	free_t_command(t_command **cmd)
{
	t_command	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->content)
			free((*cmd)->content);
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	free_t_cmd_line(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->fd_error)
			free((*cmd)->fd_error);
		if ((*cmd)->cmds)
			free_2d_table((*cmd)->cmds);
		if ((*cmd)->cmds_exe)
			free_2d_table((*cmd)->cmds_exe);
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	main_free(t_command **cmd, t_cmd_line **cmd_l, char **temp, char *str)
{
	free(temp);
	free_t_command(cmd);
	free_t_cmd_line(cmd_l);
	(void )cmd_l;
	if (str)
		free(str);
}
