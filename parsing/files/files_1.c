/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:28:24 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/22 12:10:06 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_ambiguous(char *str)
{
	if (str && (ft_strchr(str, 32) || !str[0]))
		return (1);
	return (0);
}

int	sub_files_red_in(char **infile, t_cmd_line **tmp, int *j, char **temp)
{
	int	in_q;

	if (!temp[*j])
		return (1);
	in_q = is_in_qotes(temp[*j]);
	(*infile) = extand_var(temp[*j]);
	(*infile) = remove_quotes((*infile));
	free(temp[*j]);
	(*j)++;
	if (!(*infile))
		(*infile) = ft_strdup("");
	if (in_q && is_ambiguous((*infile)))
	{
		(*tmp)->fd_error = ft_strdup((*infile));
		(*tmp)->flag = 3;
		printf("ambiguous redirect\n");
		g_gv->exit_status = 1;
		if ((*infile))
			free((*infile));
		return (1);
	}
	return (0);
}

int	files_red_in(char **temp, t_cmd_line **tmp, int *j)
{
	char	*infile;

	if (sub_files_red_in(&infile, tmp, j, temp))
		return (1);
	(*tmp)->infile = open(infile, O_RDONLY);
	(*tmp)->index_infile = *j;
	(*tmp)->fd_error = NULL;
	if ((*tmp)->infile < 0)
	{
		(*tmp)->fd_error = ft_strdup(infile);
		(*tmp)->flag = 3;
		perror((*tmp)->fd_error);
		g_gv->exit_status = 1;
		if (infile)
			free(infile);
		return (1);
	}
	if (infile)
		free(infile);
	return (0);
}

int	sub_files_red_out(char **outfile, t_cmd_line **tmp, int *j, char **temp)
{
	int	in_q;

	if (!temp[*j])
		return (1);
	in_q = is_in_qotes(temp[*j]);
	(*outfile) = extand_var(temp[*j]);
	(*outfile) = remove_quotes((*outfile));
	free(temp[*j]);
	(*j)++;
	if (!(*outfile))
		(*outfile) = ft_strdup("");
	if (in_q && is_ambiguous((*outfile)))
	{
		(*tmp)->fd_error = ft_strdup((*outfile));
		(*tmp)->flag = 4;
		printf("ambiguous redirect\n");
		g_gv->exit_status = 1;
		if ((*outfile))
			free((*outfile));
		return (1);
	}
	return (0);
}

int	files_red_out(char **temp, t_cmd_line **tmp, int *j)
{
	char	*outfile;

	if (sub_files_red_out(&outfile, tmp, j, temp))
		return (1);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	(*tmp)->fd_error = NULL;
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		(*tmp)->flag = 4;
		perror((*tmp)->fd_error);
		g_gv->exit_status = 1;
		if (outfile)
			free(outfile);
		return (1);
	}
	if (outfile)
		free(outfile);
	return (0);
}
