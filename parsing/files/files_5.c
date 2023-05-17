/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:05 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/17 22:08:03 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**ft_join_2d(char **tab1, char **tab2, int p)
{
	char	**new_tab;
	int		cont;
	int		cont1;
	int		i;

	new_tab = malloc(sizeof(char *) * (strlen_2d(tab1) + strlen_2d(tab2) + 1));
	if (!new_tab)
		return (NULL);
	cont1 = 0;
	cont = -1;
	while (tab1[++cont])
	{
		if (cont != p)
		{
			new_tab[cont1] = ft_strdup(tab1[cont]);
			cont1++;
		}
	}
	i = -1;
	while (tab2[++i])
		new_tab[cont1++] = ft_strdup(tab2[i]);
	new_tab[cont1] = 0;
	free_2d_table(tab2);
	free(tab1);
	return (new_tab);
}

void	extand_in_comamnd_struct(t_cmd_line **tmp, int *j)
{
	char	*temp1;
	char	**temp2;
	char	*t_mp;
	char	*t_mp1;

	t_mp = (*tmp)->cmds[(*j)];
	(*tmp)->cmds[(*j)] = extand_var((*tmp)->cmds[(*j)]);
	if ((*tmp)->cmds[(*j)] && ft_strcmp(t_mp, (*tmp)->cmds[(*j)]))
	{
		if (ft_strchr(t_mp, '$'))
			(*tmp)->cmds[(*j)] = remove_quotes((*tmp)->cmds[(*j)]);
		if (!ft_strchr(t_mp, '\"') && (ft_strchr((*tmp)->cmds[(*j)], ' ')
			|| ft_strchr((*tmp)->cmds[(*j)], '\t')))
		{
			temp1 = remove_quotes((*tmp)->cmds[(*j)]);
			t_mp1 = temp1;
			temp1 = set_spliter(temp1, ' ');
			if(t_mp1)
				free(t_mp1);
			temp2 = ft_split(temp1, -1);
			if (temp1)
				free(temp1);
			(*tmp)->cmds = ft_join_2d((*tmp)->cmds, temp2, (*j));
		}
	}
	else
		(*tmp)->cmds[(*j)] = remove_quotes((*tmp)->cmds[(*j)]);
	if (t_mp)
		free(t_mp);
	(*j)++;
}

int	open_read_out_in(char **temp, t_cmd_line **tmp, int *j)
{
	if (!ft_strcmp(temp[(*j)], "<"))
	{
		free(temp[(*j)]);
		(*j)++;
		if (files_red_in(temp, tmp, j))
			return (1);
	}
	else if (!ft_strcmp(temp[(*j)], ">"))
	{
		free(temp[(*j)]);
		(*j)++;
		if (files_red_out(temp, tmp, j))
			return (1);
	}
	return (0);
}

int	open_appnd_herdoc(char **temp, t_cmd_line **tmp, int *j)
{
	if (!ft_strcmp(temp[(*j)], ">>"))
	{
		free(temp[(*j)]);
		(*j)++;
		if (files_append(temp, tmp, j))
			return (1);
	}
	else if (!ft_strcmp(temp[(*j)], "<<"))
	{
		free(temp[(*j)]);
		(*j)++;
		if (!temp[(*j)])
			return (1);
		files_here_doc(temp, tmp, j);
		if (g_gv->exit_status == 1)
			return (1);
	}
	return (0);
}
