/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/05 18:40:54 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_pipes(int num_pipes, int **pipefd)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
}

static void	free_2d_table(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		// free(t[i]);
		i++;
	}
	// free(t);
}

void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(127);
}
int check_command_builtins(char *command)
{
	if (command)
	{
		if (!ft_strcmp(command,"echo"))
			return 0;
		else if (!ft_strcmp(command,"pwd"))
			return 0;
		else if (!ft_strcmp(command,"cd"))
			return 0;
		else if (!ft_strcmp(command,"env"))
			return 0;
		else if (!ft_strcmp(command,"exit"))
			return 0;
		else if (!ft_strcmp(command,"export"))
			return 0;
	}
	return 1;
}
void	child(int num_pipes, int i, int **pipefd, t_cmd_line *cmd_l)
{
	if (cmd_l->fd_error)
		exit(1);
	char *path = get__path(cmd_l->cmds[0]);
	int flag_command =  check_command_builtins(cmd_l->cmds[0]);
	if (flag_command && cmd_l->cmds[0] && !ft_strchr(cmd_l->cmds[0], '/')
			&& (access(path, F_OK) == -1 || !ft_strcmp(cmd_l->cmds[0], "")))
		cmd_not_found(cmd_l->cmds[0]);
	if (!cmd_l->cmds[0])
		exit(0);
	if (cmd_l->infile != -1)
	{
		dup2(cmd_l->infile, 0);
		close(cmd_l->infile);
	}
	else if (i != 0)
	{
		dup2(pipefd[i - 1][0], 0);
		close(pipefd[i - 1][0]);
	}
	if (cmd_l->outfile != -1)
	{
		dup2(cmd_l->outfile, 1);
		close(cmd_l->outfile);
	}
	else if (i != num_pipes)
	{
		dup2(pipefd[i][1], 1);
		close(pipefd[i][1]);
	}
	ft_execution(cmd_l);
}

void	sub2_pipex(int num_pipes,int num_cmds,  int **pipefd, int *pids, t_cmd_line *cmd_l)
{
	int		i;
	char	**command;

	i = -1;
	while (++i < num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			return ;
		}
		if (pids[i] == 0)
			child(num_pipes , i, pipefd, cmd_l);
		waitpid(pids[i], 0, 0);
		cmd_l  = cmd_l->next;
		if (i != num_cmds - 1)
			close(pipefd[i][1]);
	}
}
int 	count_pipes(t_cmd_line *cmd_l)
{
	int i = 0;
	while(cmd_l)
	{
		cmd_l = cmd_l->next;
		i++;
	}
	return i;
}
void	pipex(t_cmd_line *cmd_l)
{
	int	*pids;
	int	i;
	int	**pipefd;
	int num_pipes;
	int num_cmds;

	num_cmds = count_pipes(cmd_l);
	num_pipes = count_pipes(cmd_l) - 1;
	if (num_pipes < 0)
		num_pipes = 0;
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
	pids = malloc(sizeof(int) * num_cmds);
	if (!pids)
		exit(1);
	open_pipes(num_pipes, pipefd);
	sub2_pipex(num_pipes, num_cmds, pipefd, pids, cmd_l);
}
