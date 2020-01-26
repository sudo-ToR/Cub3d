/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:39:41 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/14 20:30:10 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i])
			i++;
	}
	return (count);
}

static char	*ft_cpy(char const *s, char c)
{
	int		i;
	char	*dest;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (dest == 0)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**r;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	count = ft_count_word(s, c);
	if (!(r = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		while (s[j] == c && s[j])
			j++;
		r[i] = ft_cpy(&s[j], c);
		if (r[i] == 0)
			return (NULL);
		while (s[j] != c && s[j])
			j++;
		i++;
	}
	r[i] = 0;
	return (r);
}
