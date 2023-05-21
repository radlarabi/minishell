/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:55:02 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/21 16:56:38 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	sub_open_files(char **temp, t_cmd_line **tmp, int *j)
{
	if (!ft_strcmp(temp[(*j)], ">>"))
	{
		if (open_appnd_herdoc(temp, tmp, j))
			return (1);
	}
	else if (!ft_strcmp(temp[(*j)], "<") || !ft_strcmp(temp[(*j)], ">"))
	{
		if (open_read_out_in(temp, tmp, j))
			return (1);
	}
	else if (!ft_strcmp(temp[(*j)], "<<"))
	{
		free(temp[(*j)++]);
		free(temp[(*j)++]);
	}
	return (0);
}
