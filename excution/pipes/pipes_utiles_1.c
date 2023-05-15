/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utiles_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:31:24 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/16 00:23:26 by hlakhal-         ###   ########.fr       */
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

void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(127);
}

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

void	command_builtins(t_cmd_line **cmd_l)
{
	if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "exit"))
		ft_exit(cmd_l, 0);
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

void	dup_files_and_pipes(t_cmd_line *cmd_l, int **pipefd, int i,
		int num_pipes)
{
	if (cmd_l->infile != -1)
	{
		dup2(cmd_l->infile, 0);
		close(cmd_l->infile);
	}
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
