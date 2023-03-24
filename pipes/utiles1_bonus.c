/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:51:55 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/11 21:13:33 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(t_cmd_line *cmd, int **pipefd)
{
	int	j;

	j = 0;
	while (j < cmd->num_pipes)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
}

void	open_pipes(t_cmd_line *cmd, int **pipefd)
{
	int	i;

	i = 0;
	while (i < cmd->num_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			print_error("");
		i++;
	}
}

void	open_infile(t_cmd_line *cmd)
{
	int	in;

	in = open(cmd->infile, O_RDONLY);
	if (in == -1)
		print_error(cmd->infile);
	dup2(in, 0);
	close(in);
}

void	open_outfile(t_cmd_line *cmd)
{
	int	out;

	out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out == -1)
		print_error(cmd->outfile);
	dup2(out, 1);
	close(out);
}

void	in_pipe(t_cmd_line *cmd, int i, int **pipefd)
{
	if (i == 0)
		open_infile(cmd);
	else
		dup2(pipefd[i - 1][0], 0);
}
