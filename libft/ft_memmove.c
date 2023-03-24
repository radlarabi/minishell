/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:59:24 by rlarabi           #+#    #+#             */
/*   Updated: 2022/10/31 11:01:53 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_c;
	char	*src_c;

	src_c = (char *)src;
	dst_c = (char *)dst;
	if (src_c == dst_c)
		return (src_c);
	if (!src_c && !dst_c)
		return (NULL);
	if (dst_c < src_c)
		ft_memcpy(dst_c, src_c, len);
	else
	{
		while (len)
		{
			dst_c[len - 1] = src_c[len - 1];
			len--;
		}
	}
	return (dst_c);
}
