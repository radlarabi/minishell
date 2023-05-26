/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utiles_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:38:23 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/26 18:50:32 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child(int num_pipes, int i, int **pipefd, t_cmd_line *cmd_l)
{
	char	*path;

	if (cmd_l->fd_error)
		exit(1);
	if (!cmd_l->cmds[0])
		exit(g_gv->exit_status);
	path = get__path(cmd_l->cmds[0]);
	if (check_command_builtins(cmd_l->cmds[0]) && !ft_strchr(cmd_l->cmds[0],
			'/') && (access(path, F_OK) == -1 || !ft_strcmp(cmd_l->cmds[0],
				"")))
		cmd_not_found(cmd_l->cmds[0]);
	dup_files_and_pipes(cmd_l, pipefd, i, num_pipes);
	ft_execution(cmd_l);
}

void	wait_for_child(int *pids, int i)
{
	int	status;

	if (i > 0)
	{
		waitpid(pids[i - 1], &status, 0);
		while (wait(NULL) != -1)
			;
		if (WIFEXITED(status))
			g_gv->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_gv->exit_status = WTERMSIG(status) + 128;
	}
}

void	close_file_pipes(t_cmd_line *cmd, int **pipefd, t_num_p_cmds num)
{
	int	i;

	i = -1;
	while (++i < num.num_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	while (cmd)
	{
		close(cmd->infile);
		close(cmd->outfile);
		close(cmd->fd_herdoc);
		cmd = cmd->next;
	}
}

void	sub2_pipex(t_num_p_cmds num, int **pipefd, int *pids, t_cmd_line *cmd_l)
{
	int			i;
	t_cmd_line	*tmp;
	int			status;

	tmp = cmd_l;
	i = -1;
	status = 0;
	while (++i < num.num_cmds && cmd_l)
	{
		if (sub3_pipex(i, num, pipefd, &pids))
			return ;
		if (pids[i] == 0)
			child(num.num_pipes, i, pipefd, cmd_l);
		if (i > 0)
		{
			close(pipefd[i - 1][0]);
			close(pipefd[i - 1][1]);
		}
		cmd_l = cmd_l->next;
	}
	wait_for_child(pids, i);
	close_file_pipes(tmp, pipefd, num);
}

void	cmd_not_found(char *cmd)
{
	printf("command not found: %s\n", cmd);
	exit(127);
}
