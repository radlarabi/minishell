/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:53:41 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/05 19:03:34 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_node(t_env **env,char *env_var,char *env_val)
{
    t_env *new_node = malloc(sizeof(t_env));
    new_node->value = env_val;
    new_node->var = env_var;
    new_node->next = (*env);
    (*env) = new_node;
}

int check_class(char *name_of_varaibl)
{
    int i;
    i = 0;
    while (name_of_varaibl[i])
    {

        i++;
    }
    return 1;
}

int    ft_export(t_cmd_line **commands_v)
{
    t_env *tmp;
    t_cmd_line *temp;
    char *value_of_var;
    char **export_value;
    temp = (*commands_v);
    tmp = g_gv->env;
    int len;
    int i;
    int j;
    j = 1;
    i = 0;
    while (temp->cmds[i])
        i++;
    len = i;
    while (j <= len)
    {
        i = 0;
        value_of_var = temp->cmds[j];
        while (value_of_var && i < ft_strlen(value_of_var))
        {
            if (value_of_var[i] == '=')
            {
                export_value = ft_split(value_of_var,'=');
                if (!export_value)
                    return 1;
                add_node(&g_gv->env,export_value[0],export_value[1]);
            }
            i++;
        }
        if (!temp->cmds[j] && len == 1)
        {
            while (tmp)
            {
                ft_putstr_fd("declare -x ",1);
                ft_putstr_fd(tmp->var,1);
                ft_putstr_fd("=",1);
                ft_putstr_fd("\"",1);
                ft_putstr_fd(tmp->value,1);
                ft_putendl_fd("\"",1);
                tmp = tmp->next;
            }
        }
        j++;
    }
    return 0;
}