/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:04:26 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/06/01 15:50:49 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_char(char *str, char c)
{
	char	*a;
	int		i;

	if (!str)
	{
		a = malloc(sizeof(char) * 2);
		if (!a)
			return (NULL);
		a[0] = c;
		a[1] = '\0';
		free(str);
		return (a);
	}
	a = malloc(ft_strlen(str) + 2);
	if (!a)
		return (NULL);
	i = -1;
	while (str[++i])
		a[i] = str[i];
	a[i] = c;
	i++;
	a[i] = '\0';
	free(str);
	return (a);
}

char	*fill_env_var(char *ev, int *j)
{
	char	*temp;

	temp = NULL;
	while (ev[(*j)])
	{
		if (ev[(*j)] != '=')
			temp = ft_join_char(temp, ev[(*j)]);
		else if (ev[(*j)] == '=')
		{
			(*j)++;
			break ;
		}
		(*j)++;
	}
	return (temp);
}

t_env	*fill_env_node(char *env, t_env *t_env)
{
	int		i;
	char	*value;
	char	*var;

	i = 0;
	value = NULL;
	var = NULL;
	var = fill_env_var(env, &i);
	t_env->var = var;
	if (!env[i])
	{
		t_env->value = "\0";
		return (t_env);
	}
	while (env[i])
	{
		value = ft_join_char(value, env[i]);
		i++;
	}
	t_env->value = value;
	return (t_env);
}

t_env	*get_env(char **ev)
{
	int		i;
	t_env	*l_env;
	t_env	*tmp;

	i = 0;
	l_env = NULL;
	while (ev[i])
	{
		tmp = init_env();
		tmp = fill_env_node(ev[i], tmp);
		ft_add_back_env(&l_env, tmp);
		i++;
	}
	return (l_env);
}

t_env	*get_env_1(char **env)
{
	t_env	*tmp;
	int		i;
	t_env	*env_var;

	i = 0;
	env_var = NULL;
	env = env_is_null();
	while (env[i])
	{
		tmp = init_env();
		tmp = fill_env_node(env[i], tmp);
		ft_add_back_env(&env_var, tmp);
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
	return (env_var);
}
