/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:08:33 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/17 17:22:12 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_blank(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		i = -i;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	ret;

	ret = 0;
	i = skip_blank(str);
	sign = 1;
	if (i < 0)
	{
		sign = -1;
		i = -i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ret * 10 + str[i] - '0' < ret)
		{
			if (sign == 1)
				return (-1);
			else if (sign == -1)
				return (0);
		}
		ret = ret * 10 + str[i++] - '0';
	}
	return (ret * sign);
}
