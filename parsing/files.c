/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/14 14:52:42 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	files_red_in(char **temp, t_cmd_line **tmp, int *j)
{
	char *infile;

	if (!temp[++(*j)])
		return 1;
	infile = change_quote_in_files(ft_strdup(temp[(*j)]));
	// printf("INfile %s-\n", infile);
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
char *ret_in_double_quotes(char *str)
{
	int i;
	int j;
	char *ret;
	i = 0;
	j = 0;
	if (!str)
		return NULL;
	ret = malloc(ft_strlen(str));
	while(str[i])
	{
		if (str[i] == '\"')
			i++;
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return ret;
}
char *get_variable(char *str)
{
	int i = 0;
	int j = 0;
	char *ret;
	int len = 0;
	while (str[i] && str[i] == '$')
		i++;
	while(str[i] && ft_isalnum(str[i]))
		i++;
	ret = malloc(i + 1); 
	i = 0;
	while (str[i] && str[i] == '$')
		i++;
	while(str[i] && ft_isalnum(str[i]))
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = 0;
	return ret;
}

char *extand_variable(char *cmds)
{
	int i;
	int j;
	char *ret = NULL;
	j = 0;
	while(cmds[j])
	{
		if (cmds[j] == '\"')
		{
			j++;
			while(cmds[j])
			{
				if (cmds[j] == '\"')
				{
					j++;
					break;
				}
				else if (cmds[j] == '$')
				{
					j++;
					ret = ft_strjoin(ret, ft_getenv(get_variable(cmds + j)));
					j += ft_strlen(get_variable(cmds + j));
				}
				else
				{
					ret = ft_join_char(ret, cmds[j]);
					j++;
				}
			}
		}
		else if (cmds[j] == '\'')
		{
			j++;
			while(cmds[j])
			{
				if (cmds[j] == '\'')
				{
					j++;
					break;
				}
				ret = ft_join_char(ret, cmds[j]);
				j++;
			}
		}
		else
		{
			if (cmds[j] == '<' && cmds[j + 1] == '<')
			{
				ret = ft_join_char(ret, cmds[j]);
				j++;
				ret = ft_join_char(ret, cmds[j]);
				j++;
				while(cmds[j])
				{
					ret = ft_join_char(ret, cmds[j]);
					j++;
					if(cmds[j] != ' ')
						break;
				}
				while(cmds[j])
				{
				ret = ft_join_char(ret, cmds[j]);
					j++;
					if(cmds[j] == ' ')
						break;
				}
			}
			while(cmds[j] && cmds[j] != '$' && cmds[j] != '\"' && cmds[j] != '\'')
			{
				ret = ft_join_char(ret, cmds[j]);
				j++;
			}
			if (cmds[j] == '$')
			{
				j++;
				ret = ft_strjoin(ret, ft_getenv(get_variable(cmds + j)));
				j += ft_strlen(get_variable(cmds + j));
			}
		}
	}
	// printf("ret ---> %s-\n", ret);
	return ret;
}
void	free_2d_table(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

char **change_content_cmds(char **cmds)
{
	int i = 0;
	int j = 0;
	int count = 0;
	char **ret;
	while(cmds[i])
	{
		if (!ft_strcmp(cmds[i], "<<") || !ft_strcmp(cmds[i], "<")
		|| !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>"))
			count++;
		i++;
	}
	ret = malloc(sizeof(char *) * (i - (count * 2) + 1));
	// printf("########%d\n", i - (count * 2) + 1);
	i = 0;
	while(cmds[i])
	{
		while (cmds[i] && (!ft_strcmp(cmds[i], "<<") || !ft_strcmp(cmds[i], "<")
		|| !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>")))
			i += 2;
		// printf("*****%s\n", cmds[i]);
		if (!cmds[i])
			break;
		ret[j] = ft_strdup(cmds[i]);
	// exit(0);
		i++;
		j++;
	}
	ret[j] = 0;
	return ret;
}

t_cmd_line *commands_struct(char **cmds)
{
	t_cmd_line *cmd_l = NULL;
	t_cmd_line *tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	char *t1;
	char *t2;
	char **temp;

	while (cmds[i])
	{
		tmp = lst_init_cmds();
		t1 = NULL;
		cmds[i] = set_spliter(cmds[i], ' ');
		cmds[i] = extand_variable(cmds[i]);
		tmp->cmds = ft_split(cmds[i], -1);
		tmp->cmds = change_content_cmds(tmp->cmds);
		// exit(0);
		// k = 0;
		// while(tmp->cmds[k])
		// {
		// 	printf("cmd[%d] -%s-\n", k, tmp->cmds[k]);
		// 	k++;
		// }
		temp = ft_split(cmds[i], -1);
		j = 0;
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
				files_here_doc(temp, tmp, &j);
			j++;
		}
		//tmp->cmds = splite_with_space(t1);
		// printf("t1 ----> %s\n", t1);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
		free_2d_table(temp);
	}
	return cmd_l;
}