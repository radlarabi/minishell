/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/06/03 22:38:35 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_cmd_line *cmd_l)
{
	int	i;

	i = 0;
	while (cmd_l)
	{
		cmd_l = cmd_l->next;
		i++;
	}
	return (i);
}

void	free_int(int **pipefd, int *pids, int num_pipes)
{
	int	i;

	i = 0;
	if (pids)
		free(pids);
	while (num_pipes && pipefd && pipefd[i])
	{
		if (pipefd[i])
			free(pipefd[i]);
		i++;
		num_pipes--;
	}
	if (pipefd)
		free(pipefd);
}

int	**alloc_pipefd(int num_pipes)
{
	int	**pipefd;
	int	i;

	pipefd = malloc(sizeof(int *) * num_pipes);
	if (!pipefd)
		exit(1);
	i = -1;
	while (++i < num_pipes)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
			exit(1);
	}
	return (pipefd);
}

void	single_buildins_cmd(t_cmd_line *cmd_l)
{
	int	std_out;

	std_out = dup(1);
	if (cmd_l->outfile != -1)
	{
		dup2(cmd_l->outfile, STDOUT_FILENO);
		close(cmd_l->outfile);
	}
	command_builtins(&cmd_l, 0);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

void	pipex(t_cmd_line *cmd_l)
{
	int				*pids;
	int				**pipefd;
	t_num_p_cmds	num;

	if (cmd_l && cmd_l->cmds && !cmd_l->cmds[0]
		&& ((cmd_l->infile == -1 && !cmd_l->flag)
			|| (cmd_l->outfile == -1 && !cmd_l->flag)))
		return ;
	num.num_cmds = count_pipes(cmd_l);
	num.num_pipes = count_pipes(cmd_l) - 1;
	if (num.num_pipes < 0)
		num.num_pipes = 0;
	if (!num.num_pipes && cmd_l && cmd_l->cmds
		&& !check_command_builtins(cmd_l->cmds[0]))
	{
		single_buildins_cmd(cmd_l);
		return ;
	}
	pipefd = alloc_pipefd(num.num_pipes);
	pids = malloc(sizeof(int) * num.num_cmds);
	if (!pids)
		return ;
	sub2_pipex(num, pipefd, pids, cmd_l);
	free_int(pipefd, pids, num.num_pipes);
}
