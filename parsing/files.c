/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:38:03 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/11 00:09:04 by rlarabi          ###   ########.fr       */
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
	// printf("ret ---> %s\n", ret);
	return ret;
}
// char **extand_variable(char **cmds)
// {
// 	int i;
// 	int j;
// 	char *ret;
// 	i = 0;
// 	while(cmds[i])
// 	{
// 		j = 0;
// 		ret = NULL;
// 		while(cmds[i][j])
// 		{
// 			if (cmds[i][j] == '\"')
// 			{
// 				j++;
// 				while(cmds[i][j] && cmds[i][j] != '\"')
// 				{
// 					if (cmds[i][j] == '$')
// 					{
// 						j++;
// 						ret = ft_strjoin(ret, ft_getenv(get_variable(cmds[i] + j)));
// 						j += ft_strlen(get_variable(cmds[i] + j));
// 					}
// 					else
// 					{
// 						ret = ft_join_char(ret, cmds[i][j]);
// 						j++;
// 					}
// 				}
// 			}
// 			else if (cmds[i][j] == '\'')
// 			{
// 				j++;
// 				while(cmds[i][j] && cmds[i][j] != '\'')
// 				{
// 					ret = ft_join_char(ret, cmds[i][j]);
// 					j++;
// 				}
// 			}
// 			else
// 			{
// 				while(cmds[i][j] && cmds[i][j] != '$')
// 				{
// 					ret = ft_join_char(ret, cmds[i][j]);
// 					j++;
// 				}
// 				if (cmds[i][j] == '$')
// 				{
// 					j++;
// 					ret = ft_strjoin(ret, ft_getenv(get_variable(cmds[i] + j)));
// 					j += ft_strlen(get_variable(cmds[i] + j));
// 				}
// 			}
// 		}
// 		if (ret)
// 			printf("ret ---> %s\n", ret);
// 		i++;
// 	}
// 	return cmds;
// }
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
t_cmd_line *commands_struct(char **cmds)
{
	t_cmd_line *cmd_l = NULL;
	t_cmd_line *tmp;
	int i = 0;
	int j = 0;
	char *t1;
	char **temp;
	while (cmds[i])
	{
		temp = splite_with_space(extand_variable(cmds[i]));
		printf("ret ---> %s\n", extand_variable(cmds[i]));
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
				files_here_doc(temp, tmp, &j);
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
		free_2d_table(temp);
	}
	return cmd_l;
}