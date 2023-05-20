/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:05 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/20 19:16:28 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**link_2d_table(char **tab1, char **tab2, int p)
{
	char	**new_tab;
	int		i;
	int		j;
	int		k;

	new_tab = malloc(sizeof(char *) * (strlen_2d(tab1) + strlen_2d(tab2) + 1));
	if (!new_tab)
		return (NULL);
	j = 0;
	i = -1;
	while (++i < p)
		new_tab[j++] = ft_strdup(tab1[i]);
	k = -1;
	while (tab2[++k])
		new_tab[j++] = ft_strdup(tab2[k]);
	while (tab1[++i])
	{
		if (i != p)
			new_tab[j++] = ft_strdup(tab1[i]);
	}
	new_tab[j] = 0;
	free_2d_table(tab2);
	free_2d_table(tab1);
	return (new_tab);
}

void	add_in_midel_of_struct(t_cmd_line **tmp, char *t_mp, int *j)
{
	char	*temp1;
	char	*temp3;
	char	**temp2;
	char	*t_mp1;

	if (ft_strchr(t_mp, '$'))
		(*tmp)->cmds[(*j)] = remove_quotes((*tmp)->cmds[(*j)]);
	if (!ft_strchr(t_mp, '\"') && (ft_strchr((*tmp)->cmds[(*j)], ' ')
			|| ft_strchr((*tmp)->cmds[(*j)], '\t')))
	{
		temp3 = ft_strdup((*tmp)->cmds[(*j)]);
		temp1 = remove_quotes(temp3);
		t_mp1 = temp1;
		temp1 = set_spliter(temp1, ' ');
		if (t_mp1)
			free(t_mp1);
		temp2 = ft_split(temp1, -1);
		if (temp1)
			free(temp1);
		(*tmp)->cmds = link_2d_table((*tmp)->cmds, temp2, (*j));
	}
}

void	extand_in_comamnd_struct(t_cmd_line **tmp, int *j)
{
	char	*t_mp;

	t_mp = (*tmp)->cmds[(*j)];
	(*tmp)->cmds[(*j)] = extand_var((*tmp)->cmds[(*j)]);
	if ((*tmp)->cmds[(*j)] && ft_strcmp(t_mp, (*tmp)->cmds[(*j)]))
		add_in_midel_of_struct(tmp, t_mp, j);
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
	return (0);
}
