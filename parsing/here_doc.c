/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:56:30 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/12 16:21:13 by hlakhal-         ###   ########.fr       */
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
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

int	is_in_qotes(char *str)
{
	int i;

	i = 0;
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		return 0;
	return 1;
}

int	files_here_doc(char **temp, t_cmd_line **tmp, int *j,int flag)
{
	int		status;
	pid_t	pid;
	int		in_q;
	int 	fd[2];
	char *tab;
	in_q = 1;
	signal(SIGINT, SIG_IGN);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return -1;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		//printf("======================>%p\n",temp[*j]);
		if (!temp[(*j)])
		{
			close(fd[1]);
			close(fd[0]);
			free(tab);
			exit (1);
		}
		in_q = is_in_qotes(temp[*j]);
		tab = change_quote_in_files(temp[*j]);
		fill_content_heredoc(tab, fd[1], in_q);
		free(tab);
		free(temp[*j]);
		close(fd[1]);
		close(fd[0]);
		exit(0);
	}
	waitpid(pid, &g_gv->exit_status, 0);
	g_gv->exit_status = WEXITSTATUS(g_gv->exit_status);
	printf("==========>%d\n",g_gv->exit_status);
	(*tmp)->infile = fd[0];
	(*tmp)->index = flag;
	close(fd[1]);
	free(temp[(*j)++]);
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
int	fill_content_heredoc(char *stop, int fd, int in_q)
{
	char *str = NULL;
	char *content = NULL;
	char *temp;

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
		{
			temp = content;
			content = extand_var(content);
			free(temp);
		}
		write(fd, content, ft_strlen(content));
		free(content);
		free(str);
	}
	return (0);
}
