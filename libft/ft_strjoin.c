/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:18:56 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/26 16:26:50 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a_len;
	int		b_len;
	int		i;
	char	*ret;

	if (!s2)
		return (NULL);
	if (!s1)
		return ft_strdup(s2);
	a_len = ft_strlen((char *)s1);
	b_len = ft_strlen((char *)s2);
	i = -1;
	ret = (char *)malloc(sizeof(char) * (a_len + b_len + 1));
	if (!ret)
		return (0);
	while (s1[++i])
		ret[i] = s1[i];
	i = -1;
	while (s2[++i])
		ret[a_len + i] = s2[i];
	ret[a_len + i] = '\0';
	return (ret);
}
