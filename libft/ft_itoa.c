/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:26:19 by rlarabi           #+#    #+#             */
/*   Updated: 2022/10/29 18:16:42 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(long l)
{
	int	count;

	count = 0;
	if (l <= 0)
		count++;
	while (l)
	{
		l /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	l;
	int		i;
	int		len;

	l = (long)n;
	i = 0;
	len = count_numbers(l);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (0);
	ret[len] = '\0';
	if (l == 0)
		ret[0] = 48;
	if (l < 0)
	{
		ret[i] = '-';
		l *= -1;
	}
	while (l > 0)
	{
		ret[len - ++i] = (l % 10) + 48;
		l /= 10;
	}
	return (ret);
}
