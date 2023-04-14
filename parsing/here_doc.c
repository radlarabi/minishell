/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:56:30 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/14 15:32:58 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_stop_heredoc(char *str)
{
	int		i;
	char	**a;

	i = 0;
	a = splite_with_space(str);
	return (change_quote_in_files(a[0]));
}

void	sigint_handler(int sig)
{
	write(1, "\n", 1);
	exit(1);
}

int	files_here_doc(char **temp, t_cmd_line *tmp, int *j)
{
	int		status;
	pid_t	pid;
	char	*stop;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		if (!temp[++(*j)])
			exit (1);
		stop = get_stop_heredoc(temp[*j]);
		if (tmp->infile != -1)
			close(tmp->infile);
		tmp->infile = fill_content_heredoc(stop);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (0);
}
char	*change_quote_in_files(char *str)
{
	int		i;
	char	*a;

	i = 0;
	a = ft_strdup("");
	if (!str)
		return (ft_strdup(""));
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				a = ft_join_char(a, str[i]);
				i++;
			}
			if (!str[i])
				break ;
			if ('\"')
				i++;
			if (!str[i])
				break ;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				a = ft_join_char(a, str[i]);
				i++;
			}
			if (!str[i])
				break ;
			if ('\'')
				i++;
			if (!str[i])
				break ;
		}
		else
		{
			a = ft_join_char(a, str[i]);
			i++;
		}
	}
	return (a);
}
int	fill_content_heredoc(char *stop)
{
	char *str = NULL;
	char *content = NULL;
	int fd[2];
	pipe(fd);
	while (1)
	{
		str = readline(">");
		if (!ft_strcmp(str, stop))
		{
			close(fd[1]);
			break ;
		}
		content = ft_strjoin(content, str);
		content = ft_strjoin(content, "\n");
		write(fd[1], content, ft_strlen(content));
		free(content);
		free(str);
	}
	return (fd[0]);
}
