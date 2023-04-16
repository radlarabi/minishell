/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:13:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/16 02:01:00 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_line *lst_init_cmds()
{
	t_cmd_line *cmd_l = malloc(sizeof(t_cmd_line));
	cmd_l->infile = -1;
	cmd_l->outfile = -1;
	cmd_l->index = -1;
	cmd_l->next = NULL;
	cmd_l->cmds = NULL;
	cmd_l->here_f = NULL;
	cmd_l->fd_error = NULL;
	return cmd_l;
}

t_command	*init_cmd(t_command	*cmd)
{
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->content = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->type = 0;
	cmd->opr = 0;
	cmd->len = 0;
	cmd->state = 0;
	return (cmd);
}
