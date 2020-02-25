/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:43:18 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/09 14:23:58 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_find_charset(char str, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (str == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_m(char *src, char *charset)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && ft_find_charset(src[i], charset) == 0)
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == 0)
		return (0);
	i = 0;
	while (src[i] && ft_find_charset(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_count_word(char *str, char *charset)
{
	int i;
	int length;

	i = 0;
	length = 0;
	while (str[i])
	{
		while (ft_find_charset(str[i], charset) == 1 && str[i])
			i++;
		if (str[i])
			length++;
		while (str[i] && ft_find_charset(str[i], charset) == 0)
			i++;
	}
	return (length);
}

char	**ft_split(char *str, char *charset)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char *) * (ft_count_word(str, charset) + 1));
	if (dest == 0)
		return (0);
	while (i < ft_count_word(str, charset))
	{
		while (ft_find_charset(str[j], charset) == 1 && str[j])
			j++;
		dest[i] = ft_strdup_m(&str[j], charset);
		while (ft_find_charset(str[j], charset) == 0 && str[j])
			j++;
		i++;
	}
	dest[i] = 0;
	return (dest);
}
