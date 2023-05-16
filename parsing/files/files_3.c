/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:30:54 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/16 17:22:53 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extand_var_in_double_qoutes(char **ret, char *cmds, int *j)
{
	(*ret) = ft_join_char((*ret), cmds[(*j)]);
	(*j)++;
	while (cmds[(*j)])
	{
		if (cmds[(*j)] == '\"')
		{
			(*ret) = ft_join_char((*ret), cmds[(*j)]);
			(*j)++;
			break ;
		}
		else if (cmds[(*j)] == '$' && cmds[(*j) + 1] == '?')
			extand_exit_status(ret, j);
		else if (cmds[(*j)] == '$')
			sub_extand_var_in_dq(ret, cmds, j);
		else
		{
			(*ret) = ft_join_char((*ret), cmds[(*j)]);
			(*j)++;
		}
	}
}

void	ignore_extand_in_single_quotes(char **ret, char *cmds, int *j)
{
	(*ret) = ft_join_char((*ret), cmds[(*j)]);
	(*j)++;
	while (cmds[(*j)])
	{
		if (cmds[(*j)] == '\'')
		{
			(*ret) = ft_join_char((*ret), cmds[(*j)]);
			(*j)++;
			break ;
		}
		(*ret) = ft_join_char((*ret), cmds[(*j)]);
		(*j)++;
	}
}

void	ignore_extand_in_herdoc(char **ret, char *cmds, int *j)
{
	(*ret) = ft_join_char((*ret), cmds[(*j)]);
	(*j)++;
	(*ret) = ft_join_char((*ret), cmds[(*j)]);
	(*j)++;
	while (cmds[(*j)])
	{
		(*ret) = ft_join_char((*ret), cmds[(*j)]);
		(*j)++;
		if (cmds[(*j)] != ' ')
			break ;
	}
}

int	extand_normal_var(char **ret, char *cmds, int *j)
{
	char	*var;
	char	*var_env;

	if (cmds[(*j)] == '$')
	{
		if (cmds[(*j)] == '$' && (!cmds[(*j) + 1] || cmds[(*j) + 1] == ' '))
			(*ret) = ft_join_char((*ret), cmds[(*j)]);
		(*j)++;
		if (!cmds[(*j)])
			return (1);
		var = get_variable(cmds + (*j));
		var_env = ft_getenv(var);
		if (var_env)
			(*ret) = ft_strjoin((*ret), var_env);
		(*j) += ft_strlen(var);
		if (var)
			free(var);
	}
	else
	{
		(*ret) = ft_join_char((*ret), cmds[(*j)]);
		(*j)++;
	}
	return (0);
}

int	sub_extand_var(char **ret, char *cmds, int *j)
{
	if (cmds[(*j)] == '<' && cmds[(*j) + 1] == '<')
		ignore_extand_in_herdoc(ret, cmds, j);
	else if (cmds[(*j)] == '$' && cmds[(*j) + 1] == '?')
		extand_exit_status(ret, j);
	else
	{
		if (extand_normal_var(ret, cmds, j))
			return (1);
	}
	return (0);
}
