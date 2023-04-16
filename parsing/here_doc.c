/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:56:30 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/16 01:58:48 by rlarabi          ###   ########.fr       */
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

int	files_here_doc(char **temp, t_cmd_line **tmp, int *j,int flag)
{
	int		status;
	pid_t	pid;
	char	*stop;
	int 	fd[2];

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return -1;
	}
	char *name;
	name = ft_strdup("/tmp/.herdoce_");
	name = ft_strjoin(name, ft_split(ttyname(0), '/')[1]);
	printf("name %s\n", name);
	int f = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	(*tmp)->here_f = ft_strdup(name);
	if (f < 0)
		perror("open");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		if (!temp[++(*j)])
			exit (1);
		stop = get_stop_heredoc(temp[*j]);
		if ((*tmp)->infile != -1)
			close((*tmp)->infile);
		(*tmp)->infile = fill_content_heredoc(stop, f);
	}
	(*tmp)->infile = f;
	(*tmp)->index = flag;
	waitpid(pid, &status, 0);
	if (pid == 0)
		exit(0);
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
int	fill_content_heredoc(char *stop, int fd)
{
	char *str = NULL;
	char *content = NULL;
	// int fd[2];
	// if (pipe(fd) == -1)
	// 	perror("pipe");
	while (1)
	{
		str = readline(">");
		content = NULL;
		if (!ft_strcmp(str, stop))
		{
			// close(fd);
			break ;
		}
		content = ft_strjoin(content, str);
		content = ft_strjoin(content, "\n");
		write(fd, content, ft_strlen(content));
		free(content);
		free(str);
	}
	return (0);
}
