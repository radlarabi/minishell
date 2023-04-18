/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:48:46 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/18 09:52:10 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// int count_pipes(t_cmd_line **cmd)
// {
//     t_cmd_line *tmp;
//     int i = 0;

//     tmp = *cmd;
//     while(tmp)
//     {
//         i++;
//         tmp = tmp->next;
//     }
//     return i;
// }
// void	print_error(char *a)
// {
// 	perror(a);
// 	exit(1);
// }
// void	open_pipes(t_cmd_line *cmd, int **pipefd, int num_pipes)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_pipes)
// 	{
// 		if (pipe(pipefd[i]) == -1)
// 			print_error("pipe");
// 		i++;
// 	}
// }
// char **get_path(t_env *env)
// {
// 	char **path = NULL;
// 	int i = 0;
// 	while(env)
// 	{
// 		if (!ft_strcmp(env->var, "PATH"))
// 		{
// 			path = ft_split(env->value, ':');
// 			break;
// 		}
// 		env = env->next;
// 	}
// 	if (path)
// 	{
// 		while(path[i])
// 		{
// 			path[i] = ft_strjoin(path[i], "/");
// 			i++;
// 		}
// 	}
// 	return path;
// }

// char *get_path_command(char **path, char *cmd)
// {
// 	int		i;
// 	char	*a;

// 	if (access(cmd, F_OK) != -1)
// 		return (cmd);
// 	i = 0;
// 	while (path[i])
// 	{
// 		path[i] = ft_strjoin(path[i], cmd);
// 		if (access(path[i], F_OK) != -1)
// 			return (path[i]);
// 		i++;
// 	}
// 	return (NULL);
// }
// void	in_pipe(t_cmd_line *cmd, int i, int **pipefd)
// {
//     if (cmd->infile != -1)
// 	{
// 		if (cmd->index == 1)
// 		{
// 			cmd->infile = open(cmd->here_f, O_RDONLY);
// 			if (cmd->infile < 0)
// 			{
// 				perror(cmd->here_f);
// 				exit(1);
// 			}
// 			dup2(cmd->infile, 0);
// 			close(cmd->infile);
// 		}	
// 		if (!cmd->index)
// 		{
// 			dup2(cmd->infile, 0);
// 			close(cmd->infile);
// 		}
// 	}
// 	else
// 	{
// 		if (i != 0)
// 		{
// 			printf("dup to 0 --> %d\n", i);
// 			dup2(pipefd[i - 1][0], 0);
// 			close(pipefd[i - 1][0]);
// 		}
// 	}
// }
// void	out_pipe(t_cmd_line *cmd, int i, int **pipefd, int num_pipes)
// {
// 	if (cmd->outfile != -1)
// 	{
// 		dup2(cmd->outfile, 1);
// 		close(cmd->outfile);
// 	}
// 	else
// 	{
// 		if (i != (num_pipes))
// 		{
// 			printf("dup to 1 --> %d\n", i);
// 			dup2(pipefd[i][1], 1);
// 			close(pipefd[i][1]);
// 		}
// 	}
// }
// void	close_pipes(t_cmd_line *cmd, int **pipefd, int num_pipes)
// {
// 	int	j;

// 	j = 0;
// 	while (j < num_pipes)
// 	{
// 		close(pipefd[j][0]);
// 		close(pipefd[j][1]);
// 		printf("close %d\n", j);
// 		j++;
// 	}
// }
// void	child(t_cmd_line *cmd, int i, int **pipefd, int num_pipes)
// {
//     if (access(get_path_command(get_path(g_gv->env), cmd->cmds[0]), F_OK) == -1)
// 	{
// 		printf("%s: command not found\n", cmd->cmds[0]);
// 		exit(0);
// 	}
//     in_pipe(cmd, i, pipefd);
//     out_pipe(cmd, i, pipefd, num_pipes);
//     printf("chiled start\n");
// 	printf("child %d %d\n", i, getpid());
// 	close_pipes(cmd, pipefd, num_pipes);
// 	execve(get_path_command(get_path(g_gv->env), cmd->cmds[0]), cmd->cmds, NULL);
// 	perror("execve");
//     exit(1);
// }
// void	sub2_pipex(t_cmd_line *cmd, int **pipefd, int *pids, int num_pipe)
// {
// 	int		i;
// 	int		num_cmd;

// 	i = -1;
// 	num_cmd = num_pipe + 1;
// 	while (++i < num_cmd)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 			print_error("fork");
// 		else if (pids[i] == 0)
// 			child(cmd, i, pipefd, num_pipe);
// 		waitpid(pids[i], 0, 0);
// 		printf("cmd [%d] --> %s for pid %d\n", i, cmd->cmds[0],getpid());
// 		cmd = cmd->next;
// 	}
// 	// waitpid(-1, 0, 0);
// 	close_pipes(cmd, pipefd, num_pipe);
// }

// void	sub1_pipex(t_cmd_line *cmd, int **pipefd, int *pids, int num_pipes)
// {
// 	int	i;

// 	close_pipes(cmd, pipefd, num_pipes);
// 	i = -1;
// 	while (++i < num_pipes)
// 		free(pipefd[i]);
// 	free(pipefd);
// 	free(pids);
// }
// void    execution(t_cmd_line *cmd)
// {
//     int	*pids;
//     int num_pipes;
//     int num_cmd;
// 	int	i;
// 	int	**pipefd;

//     num_cmd = count_pipes(&cmd);
// 	num_pipes = num_cmd - 1;
// 	if (num_cmd < 0)
// 		num_pipes = 0;
// 	pipefd = malloc(sizeof(int *) * num_pipes);
// 	if (!pipefd)
// 		exit(1);
// 	i = -1;
// 	while (++i < num_pipes)
// 	{
// 		pipefd[i] = malloc(sizeof(int) * 2);
// 		if (!pipefd[i])
// 			exit(1);
// 	}
// 	pids = malloc(sizeof(int) * num_cmd);
// 	if (!pids)
// 		exit(1);
//     open_pipes(cmd, pipefd, num_pipes);
//     sub2_pipex(cmd, pipefd, pids, num_pipes);
//     // sub1_pipex(cmd, pipefd, pids, num_pipes);
// }