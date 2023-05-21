/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:22 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/21 18:43:10 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
}

int	ft_cherch_node(char *exp_var)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = g_gv->env;
	while (temp)
	{
		if (exp_var && !ft_strcmp(temp->var, exp_var))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	check_syntax_cmd(char *cmd)
{
	size_t	cont;
	int		i;

	cont = 0;
	i = 0;
	if (cmd == NULL || cmd[0] == '\0')
		return (0);
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (1);
	while (cmd[i] != '\0')
	{
		if ((cmd[i] >= '0' && cmd[i] <= '9')
			|| (cmd[i] >= 'a' && cmd[i] <= 'z')
			|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
			|| cmd[i] == '_')
			cont += 1;
		else
			return (1);
		i++;
	}
	if (cont == ft_strlen(cmd))
		return (0);
	return (1);
}

char	**splitre_whit_pos_utils(size_t pos, size_t length, char *str)
{
	char	**result;

	result = malloc(2 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = malloc((pos + 1) * sizeof(char));
	if (!result[0])
		return (NULL);
	ft_strncpy(result[0], str, pos);
	result[0][pos] = '\0';
	result[1] = malloc((length - pos + 1) * sizeof(char));
	if (!result[1])
		return (NULL);
	ft_strncpy(result[1], str + pos, length - pos);
	result[1][length - pos] = '\0';
	return (result);
}

char	**splitre_whit_pos(char *str, size_t pos)
{
	size_t	length;
	char	**result;
	char	**new_tab;

	length = ft_strlen(str);
	if (str[pos] == '=')
	{
		if (pos >= 0 && pos < length)
		{
			new_tab = splitre_whit_pos_utils(pos, length, str);
			return (new_tab);
		}
		else
		{
			result = malloc(2 * sizeof(char *));
			if (!result)
				return (NULL);
			result[0] = ft_strdup(str);
			result[1] = NULL;
			return (result);
		}
	}
	free(str);
	return (NULL);
}
