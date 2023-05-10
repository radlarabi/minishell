/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:22 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/10 20:44:17 by rlarabi          ###   ########.fr       */
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
	int		i;
	size_t	cont;

	cont = 0;
	i = 0;
	if (ft_strchr("0123456789", cmd[0]))
		return (1);
	while (cmd && cmd[i])
	{
		if (ft_strchr("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_",
						cmd[i]))
			cont += 1;
		if (ft_strlen(cmd) == cont)
			return (0);
		i++;
	}
	return (1);
}

char	**splitre_whit_pos(char *str, size_t pos)
{
	size_t	length;
	char	**result;

	result = malloc(2 * sizeof(char *));
	length = ft_strlen(str);
	if (str[pos] == '=')
	{
		if (pos >= 0 && pos < length)
		{
			result[0] = malloc((pos + 1) * sizeof(char));
			ft_strncpy(result[0], str, pos);
			result[0][pos] = '\0';
			result[1] = malloc((length - pos + 1) * sizeof(char));
			ft_strncpy(result[1], str + pos, length - pos);
			result[1][length - pos] = '\0';
		}
		else
		{
			result[0] = ft_strdup(str);
			result[1] = NULL;
		}
	}
	return (result);
}
