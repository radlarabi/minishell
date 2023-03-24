/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:11:20 by rlarabi           #+#    #+#             */
/*   Updated: 2022/11/01 12:06:35 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_start(const char *str, char *s)
{
	int	count;

	count = 0;
	while (str[count] && ft_strchr(s, str[count]))
		count++;
	return (count);
}

static int	check_end(const char *str, char *s)
{
	int	count;
	int	str_len;

	str_len = ft_strlen(str);
	count = 0;
	while (0 < str_len && ft_strchr(s, str[str_len - 1]))
	{
		count++;
		str_len--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	len;
	char			*ret;
	int				start;
	int				end;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	start = check_start((char *)s1, (char *)set);
	end = check_end((char *)s1, (char *)set);
	if (len == (unsigned int)start || len == (unsigned int)end)
		return (ft_strdup(""));
	ret = (char *)malloc(len - start - end + 1);
	if (!ret)
		return (NULL);
	while (i < len - start - end)
	{
		ret[i] = s1[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
