/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:03:10 by rlarabi           #+#    #+#             */
/*   Updated: 2022/11/01 15:03:21 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				a;
	unsigned int	i;
	char			*str;
	char			*s;

	str = (char *)haystack;
	if (needle[0] == '\0')
		return (str);
	if (len == 0 && haystack == NULL)
		return (NULL);
	s = (char *)needle;
	a = ft_strlen(s);
	i = 0;
	while (str[i] && i < len)
	{
		if (a + i > len)
			return (NULL);
		if (s[0] == str[i] && ft_strncmp(str + i, s, a) == 0)
			return (str + i);
		i++;
	}
	return (NULL);
}
