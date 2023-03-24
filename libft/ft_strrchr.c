/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:20:44 by rlarabi           #+#    #+#             */
/*   Updated: 2022/10/29 11:14:30 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*a;
	int				i;

	i = 0;
	a = (unsigned char *)s;
	while (a[i])
		i++;
	while (i >= 0)
	{
		if (a[i] == (unsigned char)c)
			return ((char *)(&a[i]));
		i--;
	}
	return (0);
}
