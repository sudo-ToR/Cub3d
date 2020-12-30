/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:01:08 by lnoirot           #+#    #+#             */
/*   Updated: 2020/12/30 15:27:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/cub3d.h"

void		ft_realloc(int *nbr_line, char ***map, char *line)
{
	char	**tmp;
	int		i;

	if (!(tmp = malloc(sizeof(char *) * (*nbr_line + 2))))
		return ;
	i = 0;
	while (i < *nbr_line)
	{
		tmp[i] = (*map)[i];
		i++;
	}
	tmp[*nbr_line] = line;
	tmp[*nbr_line + 1] = NULL;
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

	if (check_clean_num(res, id, line))
		return (check_clean_num(res, id, line));
	i = 0;
	j = -1;
	stock = (id == 0) ? ft_split(line, " \f\t\n\r\v")
		: ft_split(line, " ,\f\t\n\r\v");
	while (stock[i])
		i++;
	if ((id == 0 && i == 3) || (id == 1 && i == 4))
	{
		if (!(*res = malloc(sizeof(int *) * i)))
			return (1);
		while (++j < i - 1)
			(*res)[j] = ft_atoi(stock[j + 1]);
	}
	else
		*res = NULL;
	free_clean_num(stock, line);
	if (res && id == 1)
		ft_swap(*res);
	return (0);
}

int			get_texture(t_pars *p, char *line, t_mlx *m)
{
	if (!(ft_strncmp(line, "NO ", 3)))
		return (error_dupplication_text(line, &p->no, m));
	else if (!(ft_strncmp(line, "SO ", 3)))
		return (error_dupplication_text(line, &p->so, m));
	else if (!(ft_strncmp(line, "S ", 2)))
		return (error_dupplication_text(line, &p->s, m));
	else if (!(ft_strncmp(line, "WE ", 3)))
		return (error_dupplication_text(line, &p->we, m));
	else if (!(ft_strncmp(line, "EA ", 3)))
		return (error_dupplication_text(line, &p->ea, m));
	return (0);
}

int			ft_pars(int fd, t_pars *p, t_mlx *m)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_isnum(line))
		{
			if (ft_pars_num(line, p))
				return (aff_error(ft_pars_num(line, p), m));
		}
		else if ((is_texture(line)) && !(p->map))
		{
			if (get_texture(p, line, m))
				return (1);
		}
		else if (!ft_strlen(line))
			empty_line_parsing(line, p, m);
		else if (is_map(line))
			ft_realloc(&p->height, &p->map, line);
		else
			wrong_arg(line, m);
	}
	ft_pars_utils_map(ret, line, p);
	return ((ret == -1) ? -1 : ft_check_parsing(p, fd, m));
}
