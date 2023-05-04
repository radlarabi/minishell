/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/04 12:09:38 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	files_red_in(char **temp, t_cmd_line **tmp, int *j)
{
	char *infile;

	++(*j);
	if (!temp[*j])
		return 1;
	infile = change_quote_in_files(ft_strdup(temp[*j]));
	if ((*tmp)->infile != -1)
		close((*tmp)->infile);
	(*tmp)->infile = open(infile, O_RDONLY);
	(*tmp)->index = 0;
	(*tmp)->fd_error  = NULL;
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

	++(*j);
	if (!temp[*j])
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

	++(*j);
	if (!temp[*j])
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
	return ret;
}
void	free_2d_table(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		// free(t[i]);
		i++;
	}
	// free(t);
}

char **change_content_cmds(char **cmds)
{
	int i;
	int j;
	int len;
	char **ret;

	i = 0;
	j = 0;
	while(cmds[i])
	{
		if (ft_strcmp(cmds[i], "<") || ft_strcmp(cmds[i], "<<") || ft_strcmp(cmds[i], ">") || ft_strcmp(cmds[i], ">>"))
			j++;
		i++;
	}
	len = j;
	ret = malloc(sizeof(char *) * (j + 1));
	if (!ret)
		return NULL;
	printf("---> len %d\n", j);
	i = 0;
	j = 0;
	while(cmds[i])
	{
		while ( (i < len) && (!ft_strcmp(cmds[i], "<") || !ft_strcmp(cmds[i], "<<") || !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>")))
			i += 2;
		if (i >= len)
			break;
		ret[j] = ft_strdup(cmds[i]);
		printf("ret[%d] --> %s\n", j, ret[j]);
		j++;
		i++;
	}
	ret[j] = 0;
	return ret;
	// exit(0);
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
	int flag;

	while (cmds[i])
	{
		tmp = lst_init_cmds();
		t1 = NULL;
		cmds[i] = set_spliter(cmds[i], ' ');
		tmp->cmds = ft_split(cmds[i], -1);
		temp = ft_split(cmds[i], -1);
		j = 0;
		while(tmp->cmds[j])
		{
			if (!ft_strcmp(tmp->cmds[j], "\"\"") || !ft_strcmp(tmp->cmds[j], "\'\'"))
				tmp->cmds[j] = ft_strdup("");
			else
				tmp->cmds[j] = extand_variable(tmp->cmds[j]);
			temp[j] = ft_strdup(tmp->cmds[j]);
			j++;
		}
		tmp->str_cmd = ft_strdup(cmds[i]);
		tmp->cmds = change_content_cmds(tmp->cmds);
		k = j;
		j = 0;
		while(j < k)
		{
			if (!ft_strncmp(temp[j], "<", ft_strlen(temp[j])))
			{
				if (files_red_in(temp, &tmp, &j))
					break;
			}
			else if (!ft_strncmp(temp[j], ">", ft_strlen(temp[j])))
			{
				if (files_red_out(temp, &tmp, &j))
					break;
			}
			else if (!ft_strncmp(temp[j], ">>", ft_strlen(temp[j])))
			{
				if (files_append(temp, &tmp, &j))
					break;
			}
			else if (!ft_strncmp(temp[j], "<<", ft_strlen(temp[j])))
			{
				flag = 1;
				files_here_doc(temp, &tmp, &j,flag);
			}
			j++;
		}
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
		free_2d_table(temp);
	}
	return cmd_l;
}
