/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:13:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/21 16:30:54 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_line	*lst_init_cmds(void)
{
	t_cmd_line	*cmd_l;

	cmd_l = malloc(sizeof(t_cmd_line));
	if (!cmd_l)
		return (NULL);
	cmd_l->infile = -1;
	cmd_l->fd_herdoc = -1;
	cmd_l->index_herdoc = 0;
	cmd_l->index_infile = 0;
	cmd_l->outfile = -1;
	cmd_l->flag = 0;
	cmd_l->next = NULL;
	cmd_l->cmds = NULL;
	cmd_l->cmds_exe = NULL;
	cmd_l->fd_error = NULL;
	return (cmd_l);
}

t_command	*init_cmd(t_command *cmd)
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

void	ft_add_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

t_env	*init_env(void)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	env_var->value = NULL;
	env_var->var = NULL;
	env_var->flag = 0;
	env_var->next = NULL;
	return (env_var);
}
