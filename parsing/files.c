/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/07 23:39:05 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	files_red_in(char **temp, t_cmd_line **tmp, int *j)
{
	char *infile;

	if (!temp[++(*j)])
		return 1;
	infile = change_quote_in_files(ft_strdup(temp[(*j)]));
	if ((*tmp)->infile != -1)
		close((*tmp)->infile);
	(*tmp)->infile = open(infile, O_RDONLY);
	if ((*tmp)->infile < 0)
	{
		(*tmp)->fd_error = ft_strdup(infile);
		return 1;
	}
	return 0;
}

int	files_red_out(char **temp, t_cmd_line **tmp, int *j)
{
	char *outfile;

	if (!temp[++(*j)])
		return 1;
	outfile = change_quote_in_files(ft_strdup(temp[(*j)]));
	if ((*tmp)->outfile != -1)
		close((*tmp)->outfile);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		return 1;
	}
	return 0;
}

int	files_append(char **temp, t_cmd_line **tmp, int *j)
{
	char *outfile;

	if (!temp[++(*j)])
		return 1;
	outfile = change_quote_in_files(ft_strdup(temp[(*j)]));
	if ((*tmp)->outfile != -1)
		close((*tmp)->outfile);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		return 1;
	}
	return 0;	
}

t_cmd_line * commands_struct(char **cmds)
{
	t_cmd_line *cmd_l = NULL;
	t_cmd_line *tmp;
	int i = 0;
	int j = 0;
	char *t1;
	char **temp;
	while (cmds[i])
	{
		temp = splite_with_space(cmds[i]);
		tmp = lst_init_cmds();
		j = 0;
		t1 = NULL;
		while(temp[j])
		{
			if (!ft_strncmp(temp[j], "<", ft_strlen(temp[j])))
			{
				if (files_red_in(temp, &tmp, &j))
					break;
				printf("infile --> %d\n", tmp->infile);
			}
			else if (!ft_strncmp(temp[j], ">", ft_strlen(temp[j])))
			{
				if (files_red_out(temp, &tmp, &j))
					break;
				printf("outfile --> %d\n", tmp->outfile);
			}
			else if (!ft_strncmp(temp[j], ">>", ft_strlen(temp[j])))
			{
				if (files_append(temp, &tmp, &j))
					break;
				printf("outfile --> %d\n", tmp->outfile);
			}
			else if (!ft_strncmp(temp[j], "<<", ft_strlen(temp[j])))
			{
				files_here_doc(temp, tmp, &j);
			}
			else
			{
				t1 = ft_strjoin(t1, temp[j]);
				t1 = ft_strjoin(t1, " ");
			}
			j++;
		}
		tmp->cmds = splite_with_space(t1);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
	}
	// i = 0;
	// while(cmd_l)
	// {
	// 	j = 0;
	// 	printf("---> %d infile %s +++ outfile %s +++ \n", i++, cmd_l->infile, cmd_l->outfile);
	// 	while (cmd_l->cmds[j])
	// 	{
	// 		printf("cmd [%d] %s\n", j+1, cmd_l->cmds[j]);
	// 		j++;
	// 	}
	// 	cmd_l = cmd_l->next;
	// }
	return cmd_l;
}