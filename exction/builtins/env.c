/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:03:56 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/02 13:07:37 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env()
{
    t_env *tmp;

    tmp = g_gv->env;
    while(tmp)
    {
        printf("%s=%s\n", tmp->var, tmp->value);
        tmp = tmp->next;
    }
    exit(0);
}