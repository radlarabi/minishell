/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/08 21:12:31 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_ambiguous(char  *str)
{
	if (str && ft_strchr(str, 32))
		return 1;
	return 0;
}
int	files_red_in(char **temp, t_cmd_line **tmp, int *j)
{
	char *infile;
	int in_q;

	if (!temp[*j])
		return 1;
	in_q = is_in_qotes(temp[*j]);
	infile = extand_variable(temp[*j]);
	free(temp[*j]);
	(*j)++;
	if (!infile)
		infile = ft_strdup("");
	if (in_q && is_ambiguous(infile))
	{
		(*tmp)->fd_error = ft_strdup(infile);
		printf("ambiguous redirect\n");
		g_gv->exit_status = 1;
		if (infile)
			free(infile);
		return 1;
	}
	if ((*tmp)->infile != -1)
		close((*tmp)->infile);
	(*tmp)->infile = open(infile, O_RDONLY);
	(*tmp)->index = 0;
	(*tmp)->fd_error  = NULL;
	if ((*tmp)->infile < 0)
	{
		(*tmp)->fd_error = ft_strdup(infile);
		if (infile)
			free(infile);
		perror((*tmp)->fd_error);
		return 1;
	}
	if (infile)
		free(infile);
		
	return 0;
}

int	files_red_out(char **temp, t_cmd_line **tmp, int *j)
{
	char *outfile;
	int in_q;

	if (!temp[*j])
		return 1;
	in_q = is_in_qotes(temp[*j]);
	outfile = extand_variable(temp[*j]);
	free(temp[*j]);
	(*j)++;
	if (!outfile)
		outfile = ft_strdup("");
	if (in_q && is_ambiguous(outfile))
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		printf("ambiguous redirect\n");
		if (outfile)
			free(outfile);
		return 1;
	}
	if ((*tmp)->outfile != -1)
		close((*tmp)->outfile);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	(*tmp)->index = 0;
	(*tmp)->fd_error  = NULL;
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		perror((*tmp)->fd_error);
		if (outfile)
			free(outfile);
		return 1;
	}
	if (outfile)
			free(outfile);
	return 0;
}

int	files_append(char **temp, t_cmd_line **tmp, int *j)
{
	char *outfile;
	int in_q;

	if (!temp[*j])
		return 1;
	in_q = is_in_qotes(temp[*j]);
	outfile = extand_variable(temp[*j]);
	free(temp[*j]);
	(*j)++;
	if (!outfile)
		outfile = ft_strdup("");
	if (in_q && is_ambiguous(outfile))
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		printf("ambiguous redirect\n");
		if (outfile)
			free(outfile);
		return 1;
	}
	if ((*tmp)->outfile != -1)
		close((*tmp)->outfile);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		perror((*tmp)->fd_error);
		if (outfile)
			free(outfile);
		return 1;
	}
	if (outfile)
			free(outfile);
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
				else if (cmds[j] == '$' && cmds[j + 1] == '?')
				{
					ret = ft_strjoin(ret, ft_itoa(g_gv->exit_status));
					j += 2;
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
			else if (cmds[j] == '$' && cmds[j + 1] == '?')
			{
				ret = ft_strjoin(ret, ft_itoa(g_gv->exit_status));
				j += 2;
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
	i = 0;
	j = 0;
	while(cmds[i])
	{
		while ( (i < len) && (!ft_strcmp(cmds[i], "<") || !ft_strcmp(cmds[i], "<<") || !ft_strcmp(cmds[i], ">") || !ft_strcmp(cmds[i], ">>")))
			i += 2;
		if (i >= len)
			break;
		ret[j] = ft_strdup(cmds[i]);
		j++;
		i++;
	}
	ret[j] = 0;
	free_2d_table(cmds);
	return ret;
}

t_cmd_line *commands_struct(char **cmds)
{
	t_cmd_line *cmd_l = NULL;
	t_cmd_line *tmp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;
	char **temp;
	char *t_mp;
	int flag;

	while (cmds[i])
	{
		tmp = lst_init_cmds();
		t_mp = cmds[i];
		cmds[i] = set_spliter(cmds[i], ' ');
		free(t_mp);
		tmp->cmds = ft_split(cmds[i], -1);
		free(cmds[i]);
		j = 0;
		while(tmp->cmds[j])
			j++;
		temp = malloc((j + 1) * sizeof(char *));
		j = 0;
		while(tmp->cmds[j])
		{
			temp[j] = ft_strdup(tmp->cmds[j]);
			j++;
		}
		temp[j] = 0;
		j = 0;
		while(tmp->cmds[j])
		{
			if (!ft_strcmp(tmp->cmds[j], "\"\"") || !ft_strcmp(tmp->cmds[j], "\'\'"))
			{
				t_mp = tmp->cmds[j];
				tmp->cmds[j++] = ft_strdup("");
				free(t_mp);
			}
			else if (!ft_strcmp(tmp->cmds[j] , "<<"))
				j += 2;
			else if (!ft_strcmp(tmp->cmds[j] , "<"))
				j += 2;
			else if (!ft_strcmp(tmp->cmds[j] , ">"))
				j += 2;
			else if (!ft_strcmp(tmp->cmds[j] , ">>"))
				j += 2;
			else
			{
				t_mp = tmp->cmds[j];
				tmp->cmds[j] = extand_variable(tmp->cmds[j]);
				free(t_mp);
				j++;
			}
		}
		tmp->cmds = change_content_cmds(tmp->cmds);
		k = j;
		j = 0;
		while(temp[j])
		{
			if (!ft_strcmp(temp[j], "<"))
			{
				free(temp[j]);
				j++;
				if (files_red_in(temp, &tmp, &j))
				{
					break;
				}
			}
			else if (!ft_strcmp(temp[j], ">"))
			{
				free(temp[j]);
				j++;
				if (files_red_out(temp, &tmp, &j))
				{
					break;
				}
			}
			else if (!ft_strcmp(temp[j], ">>"))
			{
				free(temp[j]);
				j++;
				if (files_append(temp, &tmp, &j))
				{
					break;
				}
			}
			else if (!ft_strcmp(temp[j], "<<"))
			{
				flag = 1;
				free(temp[j]);
				j++;
				files_here_doc(temp, &tmp, &j,flag);
			}
			else
			{
				free(temp[j]);
				j++;
			}
		}
		if (temp)
			free(temp);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
	}
	return cmd_l;
}
