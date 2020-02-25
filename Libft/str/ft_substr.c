/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:30:58 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/15 12:24:54 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (r == 0)
		return (NULL);
	while (i < len && s[start])
	{
		r[i] = s[start];
		i++;
		start++;
	}
	r[i] = '\0';
	return (r);
}
