/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:44:15 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/16 02:23:00 by rlarabi          ###   ########.fr       */
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
int count_pipe_used_in_execve(t_cmd_line *cmd)
{
	int i = 0;
	while(cmd)
	{
		if (cmd->outfile != -1)
			i++;
		cmd = cmd->next;
	}
	return i;
}
void    child(t_cmd_line *cmd, int **pipefd, int i)
{
	// printf("exec %d\n", cmd->infile);
    if (cmd->infile != -1)
	{
		if (cmd->index == 1)
		{
			printf(" herdo k ===> %d\n",cmd->index);
			cmd->infile = open(cmd->here_f, O_RDONLY);
			if (cmd->infile < 0)
			{
				perror(cmd->here_f);
				exit(1);
			}
			dup2(cmd->infile, 0);
			close(cmd->infile);
		}	
		if (!cmd->index)
		{
			printf("infile ===> %d\n",cmd->index);
			dup2(cmd->infile, 0);
			close(cmd->infile);
		}
	}
	
	else
	{
		if (i != 0)
		{
			dup2(pipefd[i - 1][0], 0);
			close(pipefd[i - 1][0]);
		}
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else
	{
		if (i != count_pipes(&cmd) - count_pipe_used_in_execve(cmd) - 1)
		{
			// printf("sacsacascsacsacsacascascas\n");
			dup2(pipefd[i][1], 1);
			close(pipefd[i][1]);
		}
	}
	if (!cmd->cmds[0])
		exit(0);
	if (!ft_strcmp("exit", cmd->cmds[0]))
		exit(0);
	if (access(get_path_command(get_path(g_gv->env), cmd->cmds[0]), F_OK) == -1)
	{
		printf("%s: command not found\n", cmd->cmds[0]);
		exit(0);
	}
	// exit(0);
	execve(get_path_command(get_path(g_gv->env), cmd->cmds[0]), cmd->cmds, NULL);
	perror("execve");
}


void	close_pipes(t_cmd_line *cmd, int **pipefd, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
	while(cmd)
	{	
		if (cmd->infile != -1)
		{
			close(cmd->infile);
			printf("close infile\n");
		}
		if (cmd->outfile != -1)
			close(cmd->outfile);
		cmd = cmd->next;
	}
}

void    execution(t_cmd_line *cmd)
{
    pid_t *pids;
	t_cmd_line *tmp;
    int i;
    int num_pipes;
    int **pipefd;
    char  **command;

    num_pipes = count_pipes(&cmd) - count_pipe_used_in_execve(cmd) - 1;
	if (num_pipes < 0)
		num_pipes = 0;
    pipefd = malloc(sizeof(int *) * num_pipes);
	if (!pipefd)
	{
		perror("malloc");
		return ;
	}
	i = -1;
	while (++i < num_pipes)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
			return ;
	}
	pids = malloc(sizeof(pid_t) * (num_pipes + 1));
	
	if (!pids)
		return ;
    i = 0;
	// printf("*****%d\n", num_pipes + 1);
	while (i < num_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			perror("pipe");
		i++;
	}
    i = -1;
	tmp = cmd;
	while (cmd)
	{
		i++;
		pids[i] = fork();
		if (pids[i] == -1)
			perror("fork");
		else if (pids[i] == 0)
			child(cmd, pipefd, i);
		close(cmd->infile);
		// printf("%d\n",pids[i]);
        cmd = cmd->next;
	}
	waitpid(-1, 0, 0);
	close_pipes(tmp, pipefd, num_pipes);
	// wait(0);
	// printf("wait --> %d\n" , wait(NULL));
	// exit(0);
	// printf("hannnng\n");
}