/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:51:21 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/18 16:11:16 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t little_len;

	little_len = ft_strlen(little);
	if (ft_strncmp(little, "", 1) == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (ft_strncmp(&big[i], little, little_len) == 0
			&& i + little_len <= len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
