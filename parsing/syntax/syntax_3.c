/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:29:17 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/26 00:29:36 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	max_herdoc(t_command **cmd)
{
	t_command	*tmp;
	int			count;

	count = 0;
	tmp = *cmd;
	while(tmp)
	{
		if (tmp->type == HERDOC)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
		return 1;
	else
		return 0;
}
