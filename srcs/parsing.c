/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:01:08 by lnoirot           #+#    #+#             */
/*   Updated: 2020/12/13 18:37:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void		ft_realloc(int *nbr_line, char ***map, char *line)
{
	char	**tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char *) * (*nbr_line + 1))))
		return ;
	i = 0;
	while (i < *nbr_line)
	{
		tmp[i] = (*map)[i];
		i++;
	}
	tmp[*nbr_line] = line;
	free(*map);
	(*nbr_line)++;
	*map = tmp;
}

int			clean_texture(char *line, char **texture)
{
	char	**res;
	int		i;
	int		fd;

	i = 0;
	if (*texture)
		return (1);
	res = ft_split(line, " \f\t\n\r\v");
	free(line);
	while (res[i])
	{
		if (i == 1)
			*texture = ft_strdup(res[i]);
		else if (i > 1)
			*texture = NULL;
		free(res[i]);
		i++;
	}
	free(res);
	if ((fd = open(*texture, O_RDONLY)) == -1)
		*texture = NULL;
	close(fd);
	return (0);
}


int			clean_num(char *line, int id, int **res)
{
	char	**stock;
	int		i;
	int		j;
	
	if (*res != NULL)
		return (1);
	i = 0;
	j = 0;
	stock = (id == 0) ? ft_split(line, " \f\t\n\r\v")
		: ft_split(line, " ,\f\t\n\r\v");
	while (stock[i])
		i++;
	if ((id == 0 && i == 3) || (id == 1 && i == 4))
	{
		if (!(*res = malloc(sizeof(int *) * i)))
			return (1);
		while (j < i - 1)
		{
			(*res)[j] = ft_atoi(stock[j + 1]);
			j++;
		}
	}
	else
		*res = NULL;
	free(line);
	free_table(stock);
	if (res && id == 1)
		ft_swap(*res);
	return (0);
}

int			get_texture(t_pars *p, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (clean_texture(line, &p->no))
			return(aff_error(DUPLICATION_ARGUMENT));
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (clean_texture(line, &p->so))
			return(aff_error(DUPLICATION_ARGUMENT));
	}
	else if (!ft_strncmp(line, "S ", 2))
	{
		if (clean_texture(line, &p->s))
			return(aff_error(DUPLICATION_ARGUMENT));
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (clean_texture(line, &p->we))
			return(aff_error(DUPLICATION_ARGUMENT));
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (clean_texture(line, &p->ea))
			return(aff_error(DUPLICATION_ARGUMENT));
	}
	return (0);
}

int			ft_pars(int fd, t_pars *p)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!line[0])
			free(line);
		else if (!ft_strncmp(line, "R ", 2) && !p->map)
		{
			if (clean_num(line, 0, &p->r))
				return(aff_error(DUPLICATION_ARGUMENT));
		}
		else if (!ft_strncmp(line, "F ", 2) && !p->map)
		{
			if (clean_num(line, 1, &p->f))
				return(aff_error(DUPLICATION_ARGUMENT));
		}
		else if (!ft_strncmp(line, "C ", 2) && !p->map)
		{
			if (clean_num(line, 1, &p->c))
				return(aff_error(DUPLICATION_ARGUMENT));
		}
		else if (is_texture(line) && !p->map)
		{
			if (get_texture(p, line))
				return (1);
		}
		else if (ft_isdigit(line[0]))
			ft_realloc(&p->height, &p->map, line);
		else
			aff_error(WRONG_ARG);
	}
	if (ret == 0 && ft_isdigit(line[0]))
		ft_realloc(&p->height, &p->map, line);
	p->map += ft_clean_map(p->map, p->height);
	return ((ret == -1) ? -1 : ft_check_parsing(p, fd));
}
