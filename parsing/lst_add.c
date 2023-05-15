/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:42:13 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/16 00:36:57 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*temp;

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
	{
		temp->next = new;
		new->prev = temp;
	}
}

void	ft_lstadd_back_cmds(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*temp;

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

t_command	*init_lst_in_middle(void)
{
	t_command	*new;

	new = NULL;
	new = init_cmd(new);
	new->content = ft_strdup(" ");
	new->type = SPACE;
	new->state = GENERAL;
	new->len = 1;
	return (new);
}

void	ft_lstadd_middle(t_command **cmd)
{
	t_command	*new;
	t_command	*new1;

	new = init_lst_in_middle();
	new1 = init_lst_in_middle();
	new->next = (*cmd)->next;
	new->prev = (*cmd);
	(*cmd)->next = new;
	if ((*cmd)->prev != NULL)
	{
		new1->prev = (*cmd)->prev;
		new1->next = (*cmd);
		(*cmd)->prev->next = new1;
		(*cmd)->prev = new1;
	}
	else
	{
		free(new1->content);
		free(new1);
	}
}
