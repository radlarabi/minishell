/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:26:59 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/14 14:36:30 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	out_pipe(t_cmd_line *cmd, int i, int **pipefd)
{
	if (i == cmd->num_pipes)
		open_outfile(cmd);
	else
		dup2(pipefd[i][1], 1);
}

void	child(t_cmd_line *cmd, int i, int **pipefd, char **command)
{
	if (!check_command(cmd->path, command[0]) || cmd->cmds[i][0] == ' ')
		cmd_not_found(cmd->av[i + 2]);
	in_pipe(cmd, i, pipefd);
	out_pipe(cmd, i, pipefd);
	close_pipes(cmd, pipefd);
	execve(get_command(cmd->path, command[0]), command, cmd->ev);
	print_error("execve");
}

void	sub1_pipex(t_cmd_line *cmd, int **pipefd, int *pids)
{
	int	i;

	close_pipes(cmd, pipefd);
	waitpid(-1, 0, 0);
	i = -1;
	while (++i < cmd->num_pipes)
		free(pipefd[i]);
	free(pipefd);
	free(pids);
}

void	sub2_pipex(t_cmd_line *cmd, int **pipefd, int *pids)
{
	int		i;
	char	**command;

	i = -1;
	while (++i < cmd->num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			print_error("fork");
		command = ft_split(cmd->cmds[i], ' ');
		if (pids[i] == 0)
			child(cmd, i, pipefd, command);
		free_2d_table(command);
	}
}

void	pipex(t_cmd_line *cmd)
{
	int	*pids;
	int	i;
	int	**pipefd;

	pipefd = malloc(sizeof(int *) * cmd->num_pipes);
	if (!pipefd)
		exit(1);
	i = -1;
	while (++i < cmd->num_pipes)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
			exit(1);
	}
	pids = malloc(sizeof(int) * cmd->num_cmds);
	if (!pids)
		exit(1);
	open_pipes(cmd, pipefd);
	sub2_pipex(cmd, pipefd, pids);
	sub1_pipex(cmd, pipefd, pids);
}
