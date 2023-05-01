/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:46:08 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/01 20:44:05 by rlarabi          ###   ########.fr       */
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

// void	open_infile(t_cmd_line1 *cmd)
// {
// 	int	in;

// 	in = open(cmd->infile, O_RDONLY);
// 	if (in == -1)
// 		print_error(cmd->infile);
// 	dup2(in, 0);
// 	close(in);
// }

// void	open_outfile(t_cmd_line1 *cmd)
// {
// 	int	out;

// 	out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (out == -1)
// 		print_error(cmd->outfile);
// 	dup2(out, 1);
// 	close(out);
// }

// void	in_pipe(t_cmd_line1 *cmd, int i, int **pipefd)
// {
// 	if (i == 0)
// 		open_infile(cmd);
// 	else
// 		dup2(pipefd[i - 1][0], 0);
// }


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
// void	out_pipe(t_cmd_line1 *cmd, int i, int **pipefd)
// {
// 	if (i == cmd->num_pipes)
// 		open_outfile(cmd);
// 	else
// 		dup2(pipefd[i][1], 1);
// }
void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(1);
}
void	child(t_cmd_line1 *cmd, int i, int **pipefd, t_cmd_line *cmd_l)
{
	if (!check_command(cmd->path, cmd_l->cmds[0]))
		cmd_not_found(cmd_l->cmds[0]);
	if (cmd_l->infile != -1)
	{
		if (cmd_l->index == 1)
		{
			cmd_l->infile = open(cmd_l->here_f, O_RDONLY);
			if (cmd_l->infile < 0)
			{
				perror(cmd_l->here_f);
				exit(1);
			}
			dup2(cmd_l->infile, 0);
			close(cmd_l->infile);
		}
		if (!cmd_l->index)
		{
			dup2(cmd_l->infile, 0);
			close(cmd_l->infile);
		}

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
	else if (i != cmd->num_pipes)
	{
		dup2(pipefd[i][1], 1);
		close(pipefd[i][1]);
	}
	ft_execution(cmd_l);
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
void	sub2_pipex(t_cmd_line1 *cmd, int **pipefd, int *pids, t_cmd_line *cmd_l)
{
	int		i;
	char	**command;

	i = -1;
	while (++i < cmd->num_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			print_error("fork");
		if (pids[i] == 0)
			child(cmd, i, pipefd, cmd_l);
		waitpid(pids[i], 0, 0);
		cmd_l  = cmd_l->next;
		if (i != cmd->num_cmds - 1)
			close(pipefd[i][1]);
	}
}

void	pipex(t_cmd_line1 *cmd, t_cmd_line *cmd_l)
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
	sub2_pipex(cmd, pipefd, pids, cmd_l);
}
