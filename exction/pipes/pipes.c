/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/04 22:01:08 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *a)
{
	perror(a);
	exit(1);
}
void	open_pipes(int num_pipes, int **pipefd)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			print_error("");
		i++;
	}
}

char **get_path(t_env **env)
{
	char **path = NULL;
	int i = 0;
	t_env *tmp;
	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->var, "PATH"))
		{
			path = ft_split(tmp->value, ':');
			break;
		}
		tmp = tmp->next;
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
char *get_path_command(t_cmd_line *cmd_l, char **path, char *cmd)
{
	int		i;
	char	*a;

	printf("command %s\n", cmd_l->cmds[0]);
	if (cmd_l->cmds && ft_strchr(cmd_l->cmds[0], '/'))
	{
		printf("execve --- > \n");
		execve(cmd_l->cmds[0], cmd_l->cmds, NULL);
		perror("execve");
		exit(0);
	}
	i = 0;
	printf("path[] ---> %p\n", path);
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK) != -1)
		{
			return (path[i]);
		}
		i++;
	}
	return NULL;
}

int	check_command(t_cmd_line *cmd_l, char **path, char *cmd)
{
	int		i;
	char	*a;

	if (cmd_l->index == 1)
		return 1;
	if (!cmd || !cmd[0])
		return 0;

	if (access(cmd, F_OK) != -1 )
	{
		return (1);
	}
	i = 0;
	// exit(0);
	while (path && path[i])
	{
		if (access(ft_strjoin(path[i], cmd), F_OK) != -1)
		{
			return (1);
		}
		i++;
	}
	// exit(0);
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

void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(127);
}
void	child(int num_pipes, int i, int **pipefd, t_cmd_line *cmd_l)
{
	if (cmd_l->fd_error)
	{
		printf("%s : No such file or directory\n", cmd_l->fd_error);
		exit(1);
	}
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
			print_error("fork");
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
	// printf("num_cmds %d\nnum_pipes%d\n", num_cmds, num_pipes);
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
