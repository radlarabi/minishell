/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:56:30 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/26 18:52:03 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_qotes(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		return (0);
	return (1);
}

void	child_of_herdoc(char **temp, int fd[2], int *j)
{
	int		in_q;
	char	*tab;

	in_q = 1;
	signal(SIGINT, sigint_handler);
	in_q = is_in_qotes(temp[*j]);
	tab = remove_quotes(temp[*j]);
	fprintf(stderr, "%d %d \n", fd[0], fd[1]);
	fill_content_heredoc(tab, fd, in_q);
	free(tab);
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

int	files_here_doc(char **temp, t_cmd_line **tmp, int *j)
{
	int		status;
	pid_t	pid;
	int		in_q;
	int		fd[2];

	in_q = 1;
	signal(SIGINT, SIG_IGN);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		child_of_herdoc(temp, fd, j);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_gv->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_gv->exit_status = WTERMSIG(status) + 128;
	(close((*tmp)->fd_herdoc), close(fd[1]));
	(*tmp)->fd_herdoc = fd[0];
	(*tmp)->index_herdoc = *j;
	signal(SIGINT, signal_handler);
	return (0);
}

char	*extand_var_for_herdoc(char *str)
{
	char	*ret;
	int		j;

	j = 0;
	ret = NULL;
	if (str && str[0] == '$' && (str[1] == '\n' || str[1] == '\t'
			|| str[1] == ' '))
	{
		ret = ft_join_char(ret, '$');
		j++;
	}
	while (str && str[j])
	{
		if (str[j] == '$' && str[j + 1] == '?')
			extand_exit_status(&ret, &j);
		else if (str[j] == '$')
			sub_extand_var_in_dq(&ret, str, &j);
		else
			ret = ft_join_char(ret, str[j++]);
	}
	if (str)
		free(str);
	return (ret);
}

int	fill_content_heredoc(char *stop, int fd[2], int in_q)
{
	char	*str;
	char	*content;

	while (1)
	{
		str = readline(">");
		content = NULL;
		if (!str || !ft_strcmp(str, stop))
		{
			close(fd[1]);
			close(fd[0]);
			exit(0);
		}
		content = ft_strjoin(content, str);
		content = ft_strjoin(content, "\n");
		if (in_q)
			content = extand_var_for_herdoc(content);
		write(fd[1], content, ft_strlen(content));
		free(content);
		free(str);
	}
	return (0);
}
