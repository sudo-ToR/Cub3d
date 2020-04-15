/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:20:07 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/15 12:10:41 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(dst);
	if (dstsize != 0)
	{
		while (dst[j])
			j++;
		while (src[i] && j + 1 < dstsize)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		if (j < dstsize)
			dst[j] = '\0';
	}
	if (dstsize < len)
		return (ft_strlen(src) + dstsize);
	return (len + ft_strlen(src));
}
