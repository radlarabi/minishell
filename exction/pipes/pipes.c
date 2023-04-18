/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/18 18:32:24 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	close_pipes(t_cmd_line1 *cmd, int **pipefd)
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
void	print_error(char *a)
{
	perror(a);
	exit(1);
}
void	open_pipes(t_cmd_line1 *cmd, int **pipefd)
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

void	open_infile(t_cmd_line1 *cmd)
{
	int	in;

	in = open(cmd->infile, O_RDONLY);
	if (in == -1)
		print_error(cmd->infile);
	dup2(in, 0);
	close(in);
}

void	open_outfile(t_cmd_line1 *cmd)
{
	int	out;

	out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out == -1)
		print_error(cmd->outfile);
	dup2(out, 1);
	close(out);
}

void	in_pipe(t_cmd_line1 *cmd, int i, int **pipefd)
{
	if (i == 0)
		open_infile(cmd);
	else
		dup2(pipefd[i - 1][0], 0);
}


char **get_path(t_env *env)
{
	char **path = NULL;
	int i = 0;
	while(env)
	{
		if (!ft_strcmp(env->var, "PATH"))
		{
			path = ft_split(env->value, ':');
			break;
		}
		env = env->next;
	}
	if (path)
	{
		while(path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			i++;
		}
	}
	return path;
}
char *get_path_command(char **path, char *cmd)
{
	int		i;
	char	*a;

	if (access(cmd, F_OK) != -1)
		return (cmd);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) != -1)
			return (path[i]);
		i++;
	}
	return NULL;
}

int	check_command(char **path, char *cmd)
{
	int		i;
	char	*a;

	if (access(cmd, F_OK) != -1)
		return (1);
	i = 0;
	while (path[i])
	{
		// a = ft_strjoin(path[i], cmd);
		if (access(ft_strjoin(path[i], cmd), F_OK) != -1)
		{
			// free(a);
			return (1);
		}
		// free(a);
		i++;
	}
	return (0);
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
void	out_pipe(t_cmd_line1 *cmd, int i, int **pipefd)
{
	if (i == cmd->num_pipes)
		open_outfile(cmd);
	else
		dup2(pipefd[i][1], 1);
}
void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(1);
}
void	child(t_cmd_line1 *cmd, int i, int **pipefd, char **command)
{
	if (!check_command(cmd->path, command[0]))
		cmd_not_found(command[0]);
	if (i != cmd->num_pipes)
	{
		dup2(pipefd[i][1], 1);
		close(pipefd[i][1]);
	}
	if (i != 0)
	{
		dup2(pipefd[i - 1][0], 0);
		close(pipefd[i - 1][0]);
	}
	execve(get_path_command(get_path(g_gv->env), command[0]), command, NULL);
}

void	close_pipes_1(t_cmd_line1 *cmd, int **pipefd)
{
	int	j;

	j = 0;
	while (j < cmd->num_pipes)
	{
		close(pipefd[j][1]);
		j++;
	}
	
}
void	sub2_pipex(t_cmd_line1 *cmd, int **pipefd, int *pids)
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
		waitpid(pids[i], 0, 0);
		if (i != cmd->num_cmds - 1)
			close(pipefd[i][1]);
	}
}

void	pipex(t_cmd_line1 *cmd)
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
}