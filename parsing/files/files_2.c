/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:29:43 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/15 21:00:29 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	files_append(char **temp, t_cmd_line **tmp, int *j)
{
	char	*outfile;

	if (sub_files_red_in(&outfile, tmp, j, temp))
		return (1);
	(*tmp)->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((*tmp)->outfile < 0)
	{
		(*tmp)->fd_error = ft_strdup(outfile);
		perror((*tmp)->fd_error);
		if (outfile)
			free(outfile);
		return (1);
	}
	if (outfile)
		free(outfile);
	return (0);
}

char	*ret_in_double_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	ret = malloc(ft_strlen(str));
	if (!ret)
		return NULL;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_variable(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 0;
	while (str[i] && str[i] == '$')
		i++;
	j = i;
	while (str[i] && (str[j++] == '_' || ft_isalnum(str[i])))
		i++;
	ret = malloc(i + 1);
	if(!ret)
		return NULL;
	i = 0;
	while (str[i] && str[i] == '$')
		i++;
	k = i;
	j = 0;
	while (str[i] && (str[k++] == '_' || ft_isalnum(str[i])))
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = 0;
	return (ret);
}

void	extand_exit_status(char **ret, char *cmds, int *j)
{
	char	*exit;

	exit = ft_itoa(g_gv->exit_status);
	(*ret) = ft_strjoin((*ret), exit);
	if (exit)
		free(exit);
	(*j) += 2;
}

void	sub_extand_var_in_dq(char **ret, char *cmds, int *j)
{
	char *var;
	char *var_env;

	(*j)++;
	var = get_variable(cmds + (*j));
	var_env = ft_getenv(var);
	printf("var %s\tvar_env %s\n", var , var_env);
	if (var_env)
		(*ret) = ft_strjoin((*ret), var_env);
	(*j) += ft_strlen(var);
	if (var)
		free(var);
}
