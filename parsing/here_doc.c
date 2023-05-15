/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:56:30 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/16 00:33:19 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_stop_heredoc(char *str)
{
	int		i;
	char	**a;

	i = 0;
	a = splite_with_space(str);
	return (remove_quotes(a[0]));
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

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
	fill_content_heredoc(tab, fd[1], in_q);
	free(tab);
	free(temp[*j]);
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
	g_gv->exit_status = WEXITSTATUS(status);
	(*tmp)->infile = fd[0];
	close(fd[1]);
	free(temp[(*j)++]);
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
		{
			ret = ft_join_char(ret, str[j]);
			j++;
		}
	}
	if (str)
		free(str);
	return (ret);
}

int	fill_content_heredoc(char *stop, int fd, int in_q)
{
	char	*str;
	char	*content;

	while (1)
	{
		str = readline(">");
		content = NULL;
		if (!str || !ft_strcmp(str, stop))
		{
			close(fd);
			exit(0);
		}
		content = ft_strjoin(content, str);
		content = ft_strjoin(content, "\n");
		if (in_q)
			content = extand_var_for_herdoc(content);
		write(fd, content, ft_strlen(content));
		free(content);
		free(str);
	}
	return (0);
}
