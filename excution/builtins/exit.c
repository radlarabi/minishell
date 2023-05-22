/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:03:30 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/22 12:11:31 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalpha(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	too_many_args_exit(int flag_exit)
{
	if (!flag_exit)
		ft_putendl_fd("exit", 1);
	ft_putendl_fd("exit: too many arguments", 2);
	g_gv->exit_status = 1;
}

void	num_arg_require(t_cmd_line *temp, int flag_exit)
{
	if (!flag_exit)
		ft_putendl_fd("exit", 1);
	ft_putstr_fd(temp->cmds[1], 1);
	ft_putendl_fd(": numeric argument required", 1);
	g_gv->exit_status = 255;
	exit(g_gv->exit_status);
}

void	sub_exit(t_cmd_line *temp, int flag_exit)
{
	if (!flag_exit)
		ft_putendl_fd("exit", 1);
	if (temp->cmds[1])
		g_gv->exit_status = (unsigned char)ft_atoi(temp->cmds[1]);
	exit(g_gv->exit_status);
}

int	ft_exit(t_cmd_line **commands_v, int flag_exit)
{
	t_cmd_line	*temp;
	int			cont;
	int			j;

	if (((*commands_v)->infile == -1 && (*commands_v)->flag == 3)
		|| ((*commands_v)->outfile == -1 && (*commands_v)->flag == 4))
		return (1);
	cont = 0;
	temp = (*commands_v);
	j = 1;
	while (temp->cmds[j])
	{
		j++;
		cont++;
	}
	if (temp->cmds[1] && !check_arg(temp->cmds[1]))
		num_arg_require(temp, flag_exit);
	else if (cont > 1)
		too_many_args_exit(flag_exit);
	else
		sub_exit(temp, flag_exit);
	return (0);
}
