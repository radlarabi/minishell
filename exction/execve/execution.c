/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:44:15 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/13 17:05:50 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_pipes(t_cmd_line **cmd)
{
    t_cmd_line *tmp;
    int i = 0;

    tmp = *cmd;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return i;
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
	return (NULL);
}

void    child(t_cmd_line *cmd, int *pipefd)
{
    if (cmd->infile != -1)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	// printf("")
	execve(get_path_command(get_path(g_gv->env), cmd->cmds[0]), cmd->cmds, NULL);
	perror("execve");
}
void    execution(t_cmd_line *cmd)
{
    int *pids;
    int i;
    int num_pipes;
    int **pipefd;
    char  **command;

    num_pipes = count_pipes(&cmd);
    // pipefd = malloc(sizeof(int *) * num_pipes);
	// if (!pipefd)
	// 	return ;
	// i = -1;
	// while (++i < num_pipes)
	// {
	// 	pipefd[i] = malloc(sizeof(int) * 2);
	// 	if (!pipefd[i])
	// 		return ;
	// }
	pids = malloc(sizeof(int) * (num_pipes + 1));
	if (!pids)
		return ;
    // while (i < num_pipes)
	// {
	// 	if (pipe(pipefd[i]) == -1)
	// 		perror("pipe");
	// 	i++;
	// }
    i = -1;
	while (++i < num_pipes + 1 && cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			perror("fork");
		else if (pids[i] == 0)
			child(cmd, pipefd[i]);
        cmd = cmd->next;
		// exit(0);
	}
	waitpid(-1, 0, 0);
}