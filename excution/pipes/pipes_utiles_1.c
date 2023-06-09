/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utiles_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:31:24 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/28 16:12:33 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_command_builtins(char *command)
{
	if (command)
	{
		if (!ft_strcmp(command, "echo"))
			return (0);
		else if (!ft_strcmp(command, "pwd"))
			return (0);
		else if (!ft_strcmp(command, "cd"))
			return (0);
		else if (!ft_strcmp(command, "env"))
			return (0);
		else if (!ft_strcmp(command, "exit"))
			return (0);
		else if (!ft_strcmp(command, "export"))
			return (0);
		else if (!ft_strcmp(command, "unset"))
			return (0);
	}
	return (1);
}

void	command_builtins(t_cmd_line **cmd_l, int flag)
{
	if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "exit"))
		ft_exit(cmd_l, flag);
	if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "echo"))
		ft_echo(cmd_l);
	else if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "export"))
		ft_export(cmd_l);
	else if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "unset"))
		ft_unset(cmd_l);
	else if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "env"))
		ft_env(cmd_l);
	else if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "cd"))
		ft_cd(cmd_l);
	else if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "pwd"))
		ft_pwd(cmd_l);
}

void	dup_infile(t_cmd_line *cmd_l)
{
	if (cmd_l->index_herdoc > cmd_l->index_infile)
	{
		dup2(cmd_l->fd_herdoc, 0);
		close(cmd_l->fd_herdoc);
	}
	else
	{
		dup2(cmd_l->infile, 0);
		close(cmd_l->infile);
	}
}

void	dup_files_and_pipes(t_cmd_line *cmd_l, int **pipefd, int i,
		int num_pipes)
{
	if (cmd_l->infile != -1 || cmd_l->fd_herdoc != -1)
		dup_infile(cmd_l);
	else if (i != 0)
	{
		close(pipefd[i - 1][1]);
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
		close(pipefd[i][0]);
		dup2(pipefd[i][1], 1);
		close(pipefd[i][1]);
	}
}

int	sub3_pipex(int i, t_num_p_cmds num, int **pipefd, int **pids)
{
	if (i < num.num_pipes)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	(*pids)[i] = fork();
	if ((*pids)[i] == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}
