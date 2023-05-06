/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:04:26 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/06 14:02:43 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

t_env *init_env()
{
	t_env *env_var;
	env_var = malloc(sizeof(t_env));

	if (!env_var)
		return NULL;
	env_var->value = NULL;
	env_var->var = NULL;
	env_var->next = NULL;
	return env_var;
}

char *ft_join_char(char *str, char c)
{
	char *a;
	if (!str)
	{
		a = malloc(sizeof(char) * 2);
		if (!a)
			return NULL;
		a[0] = c;
		a[1] = '\0';
		return a;
	}
	int i = 0;
	a = malloc(ft_strlen(str) + 2);
	while(str[i])
	{
		a[i] = str[i];
		i++;
	}
	a[i] = c;
	i++;
	a[i] = '\0';
	free(str);
	return a;
}

char *fill_env_var(char *ev,int *j)
{
	char *temp;
	temp = NULL;

	while (ev[(*j)])
	{
		if (ev[(*j)] != '=')
			temp = ft_join_char(temp,ev[(*j)]);
		else if (ev[(*j)] == '=')
		{
			(*j)++;
			break;
		}
		(*j)++;
	}
	return temp;
}

t_env *fill_env_node(char *env,t_env *t_env)
{
	int i;
	i = 0;
	char *value = NULL;
	char *var;
	var = fill_env_var(env,&i);
	t_env->var = var;
	while (env[i])
	{
		value = ft_join_char(value,env[i]);
		i++;
	}
	t_env->value = value;
	return t_env;
}

t_env *get_env(char **ev)
{
	int i;
	i = 0;
	t_env *l_env;
	t_env *tmp;
	l_env = NULL;
	while (ev[i])
	{
		tmp = init_env();
		tmp = fill_env_node(ev[i],tmp);
		ft_add_back(&l_env,tmp);
		i++;
	}
	return l_env;
}
