/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/14 12:47:35 by rlarabi          ###   ########.fr       */
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
		else if (!ft_strcmp(command,"unset"))
			return 0;
	}
	return 1;
}
void	command_builtins(t_cmd_line **cmd_l)
{
	if ((*cmd_l) && !ft_strcmp((*cmd_l)->cmds[0], "exit"))
		ft_exit(cmd_l,0);
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

void	dup_files_and_pipes(t_cmd_line *cmd_l, int **pipefd, int i, int num_pipes)
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

void	child(int num_pipes, int i, int **pipefd, t_cmd_line *cmd_l)
{
	char	*path;

	if (cmd_l->fd_error)
		exit(1);
	if (!cmd_l->cmds[0])
		exit(g_gv->exit_status);
	path = get__path(cmd_l->cmds[0]);
	if ( check_command_builtins(cmd_l->cmds[0]) && !ft_strchr(cmd_l->cmds[0], '/')
			&& (access(path, F_OK) == -1  || !ft_strcmp(cmd_l->cmds[0], "")))
		cmd_not_found(cmd_l->cmds[0]);
	dup_files_and_pipes(cmd_l, pipefd, i, num_pipes);
	ft_execution(cmd_l);
}

void	sub2_pipex(t_num_p_cmds num, int **pipefd, int *pids, t_cmd_line *cmd_l)
{
	int		i;
	int		j;
	int status;

	i = -1;
	status = 0;
	while (++i < num.num_cmds && cmd_l)
	{
		if (i < num.num_pipes)
			pipe(pipefd[i]);
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			return ;
		}
		if (pids[i] == 0)
			child(num.num_pipes , i, pipefd, cmd_l);
		if (i > 0)
		{
			close(pipefd[i - 1][0]);
			close(pipefd[i - 1][1]);
		}
		cmd_l  = cmd_l->next;
	}
	if (i > 0)
	{
		waitpid(pids[i - 1], &status, 0);
		while (wait(NULL) != -1);
		g_gv->exit_status = WEXITSTATUS(status);
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

void	free_int(int **pipefd, int *pids, int num_pipes)
{
	int i;

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
	int i;

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
	return pipefd;
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
	command_builtins(&cmd_l);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

void	pipex(t_cmd_line *cmd_l)
{
	int	*pids;
	int std_out;
	int	**pipefd;
	t_num_p_cmds num;

	num.num_cmds = count_pipes(cmd_l);
	num.num_pipes = count_pipes(cmd_l) - 1;
	if (num.num_pipes < 0)
		num.num_pipes = 0;
	if (!num.num_pipes && cmd_l && !check_command_builtins(cmd_l->cmds[0]))
	{
		single_buildins_cmd(cmd_l);
		return ;
	}
	pipefd = alloc_pipefd(num.num_pipes); 
	pids = malloc(sizeof(int) * num.num_cmds);
	if (!pids)
		exit(1);
	sub2_pipex(num, pipefd, pids, cmd_l);
	free_int(pipefd, pids, num.num_pipes);
}
