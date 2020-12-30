/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:25:18 by lnoirot           #+#    #+#             */
/*   Updated: 2020/12/30 15:07:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/cub3d.h"

int		length_map(char **map, int nbr_line)
{
	int i;
	int tmp;
	int len_map;

	i = 0;
	len_map = 0;
	while (i < nbr_line)
	{
		tmp = ft_strlen(map[i]);
		len_map = (len_map < tmp) ? tmp : len_map;
		i++;
	}
	return (len_map);
}

void	flood_fill(char **map, int x, int y, t_mlx *m)
{
	map[y][x] = '1';
	if (!map[y][x + 1] || !map[y + 1] || x - 1 < 0 || y - 1 < 0 ||
			(int)ft_strlen(map[y + 1]) < x || (int)ft_strlen(map[y - 1]) < x ||
			ft_isspace(map[y][x + 1]) || ft_isspace(map[y][x - 1]) ||
			ft_isspace(map[y + 1][x]) || ft_isspace(map[y + 1][x]))
	{
		aff_error(WRONG_MAP, m);
	}
	if (map[y][x + 1] != '1')
		flood_fill(map, x + 1, y, m);
	if (map[y][x - 1] != '1')
		flood_fill(map, x - 1, y, m);
	if (map[y + 1][x] != '1')
		flood_fill(map, x, y + 1, m);
	if (map[y - 1][x] != '1')
		flood_fill(map, x, y - 1, m);
}

int		check_map(t_pars *p, int nbr_line, int len_map, t_mlx *m)
{
	t_pos_fl	tmp;
	char		**map_tmp;
	int			i;

	i = -1;
	if (check_char_map(p->map, nbr_line))
		return (WRONG_MAP);
	if (!(map_tmp = malloc(sizeof(char *) * (nbr_line + 1))))
		return (1);
	while (++i < nbr_line)
		map_tmp[i] = ft_strdup(p->map[i]);
	map_tmp[i] = NULL;
	find_map_width(p);
	get_initial_position(&(p->start_dir), *p, &tmp);
	flood_fill(map_tmp, tmp.x, tmp.y, m);
	len_map = length_map(p->map, nbr_line);
	cut_space(p);
	square_map(p);
	free_table(map_tmp);
	return (0);
}

int		ft_check_parsing(t_pars *p, int fd, t_mlx *m)
{
	int		x;
	int		y;

	m->mlx_ptr = mlx_init();
	mlx_get_screen_size(m->mlx_ptr, &x, &y);
	if (p->r[0] > x)
		p->r[0] = x;
	if (p->r[1] > y)
		p->r[1] = y;
	if (fd == -1)
		return (aff_error(WRONG_PATH_CUB_FILE, m));
	else if (!p->no || !p->so || !p->ea || !p->s || !p->we)
		return (aff_error(WRONG_TEXTURE, m));
	else if (!p->r || p->r[0] <= 0 || p->r[1] <= 0)
		return (aff_error(WRONG_RESOLUTION, m));
	else if (!p->c || p->c[0] < 0 || p->c[1] < 0 || p->c[2] < 0)
		return (aff_error(WRONG_C, m));
	else if (!p->f || p->f[0] < 0 || p->f[1] < 0 || p->f[2] < 0)
		return (aff_error(WRONG_F, m));
	else if (!p->map || (check_map(p, p->height, p->width, m)))
		return (aff_error(WRONG_MAP, m));
	return (0);
}

int		aff_error(int error, t_mlx *m)
{
	ft_printf("Error\n");
	if (error == WRONG_PATH_CUB_FILE)
		ft_printf("wrong path for cub file\n");
	else if (error == WRONG_ARG)
		ft_printf("wrong argument in cub file\n");
	else if (error == WRONG_TEXTURE)
		ft_printf("wrong texture in cub file\n");
	else if (error == WRONG_RESOLUTION)
		ft_printf("incorrect resolution\n");
	else if (error == WRONG_C)
		ft_printf("incorrect ceiling color\n");
	else if (error == WRONG_F)
		ft_printf("incorrect floor color\n");
	else if (error == WRONG_MAP)
		ft_printf("invalid map\n");
	else if (error == DUPLICATION_ARGUMENT)
		ft_printf("duplication of an argument\n");
	if (error != SUCCESS)
		return (exit_game(m, 1));
	return (0);
}
