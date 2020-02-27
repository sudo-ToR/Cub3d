/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/27 17:49:29 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>

char
	get_map_pos(t_mlx m, int x, int y)
{
	// printf("%d %d (max %d %d)\n", x, y, m.p.height, m.p.width);
	return (m.p.map[y][x]);
}

double
	check_vert(t_mlx m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.x = (((double)((double)m.pl.x - (int)m.pl.x) + 0.000001) * (double)dec);
	coord.y = coeff * coord.x;
	while (coord.x + m.pl.x < m.p.width && coord.y + m.pl.y < m.p.height)
	{
		if (coord.y + m.pl.y < 0)
			return (FLT_MAX);
		if (m.p.map[(int)(coord.y + m.pl.y)][(int)(coord.x + m.pl.x)] == '1')
		{
		// printf("Coordonnes : x = %f\t y = %f index x = %d\ty = %d\n", (double)(x), (double)(x * coeff + m.pl.y), \
		(int)((x)), (int)(x * coeff + m.pl.y));
			draw_pixel_hex(&m.minimap, (t_pos){(coord.x  + m.pl.x) * 16, (coord.y + m.pl.y) * 16}, 0xffff0000, m);
			return (sqrt(pow(coord.y, 2) + pow((double)coord.x, 2)));
		}
		coord.x += dec;
		coord.y = coeff * coord.x;
	}
	// printf("Coordonnes : x = %f\t y = %f index x = %d\ty = %d\n", (double)(x + m.pl.x), (double)(x * coeff + m.pl.y), \
		(int)((x) + m.pl.x), (int)(x * coeff + m.pl.y));
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

double
	check_hor(t_mlx m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.y = (((double)((double)m.pl.y - (int)m.pl.y) + 0.000001) * (double)dec);
	coord.x = coord.y / coeff;
	while (coord.y + m.pl.y < m.p.height && coord.x + m.pl.x < m.p.width)
	{
		// printf("Coordonnes : x = %f\t y = %f index x = %d\ty = %d\n", coord.x + m.pl.x, coord.y + m.pl.y, \
		(int)(coord.x + m.pl.x), (int)(coord.y + m.pl.y));
		if (coord.x + m.pl.x < 0)
			return (FLT_MAX);
		if (m.p.map[(int)(coord.y + m.pl.y)][(int)(coord.x + m.pl.x)] == '1')
		{
			draw_pixel_hex(&m.minimap, (t_pos){ (coord.x  + m.pl.x)* 16.0,  (coord.y + m.pl.y) * 16.0}, 0xffffffff, m);
			return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
		}
		coord.y += dec;
		coord.x = coord.y / coeff;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

double
	get_distance(double angle, t_mlx m, char *wall)
{
	double		coeff;
	t_pos_fl	distance;
	t_pos		inc;
	t_pos		coord;

	coord = (t_pos) {0};
	coeff = tan(angle);
	inc.x = (angle >= M_PI_2 && angle < 3 * M_PI_2) ? -1 : 1;
	inc.y = (angle >= 0 && angle <= M_PI) ? 1 : -1;
	distance.x = check_vert(m, coeff, inc.x);
	if (angle == 0 || angle == M_PI || angle == M_PI_2 || angle == 3 * M_PI_2)
	{
		*wall = (!angle || angle == M_PI) ? 'V' : 'H';
		return(!angle || angle == M_PI) ? distance.x : check_hor(m, coeff, inc.y);
	}
	distance.y = check_hor(m, coeff, inc.y);
	// distance.y = FLT_MAX;
	*wall = (distance.x > distance.y) ? 'H' : 'V';
	return (fmin(distance.x, distance.y));
}

void
	get_image(double cam_angle, t_mlx m)
{
	double	angle;
	int		i;
	double	var_angle;
	double	distance;
	char	wall;

	angle = - (M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3 / m.p.r[0];
	i = 0;
	while (angle <= M_PI / 6 + cam_angle && i++ < m.p.r[0])
	{
		distance = get_distance(angle, m, &wall);
		// distance = 3.5;
		// printf("angle = %f\tdistance = %f\n", angle, distance);
		draw_column(distance, m, i, wall);
		angle += var_angle;
	}
}

void
	ft_init_mlx(t_mlx m)
{
	char	v;
	double	cam_angle;

	get_initial_position(&v, m.p, &m.pl);
	init_dir_vector(v, &cam_angle);
	cam_angle = -45 * M_PI / 180;
	m.mlx_ptr = mlx_init();
	m.win_ptr = mlx_new_window(m.mlx_ptr, m.p.r[0], m.p.r[1], "Cub3D");
	create_new_img(&m, &m.render, m.p.r[0], m.p.r[1]);
	create_new_img(&m, &m.minimap, m.p.width * 17, m.p.height * 17);
	minimap(m, cam_angle);
	get_image(cam_angle, m);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.render.ref, 0, 0);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.minimap.ref, 50, 50);
	mlx_loop(m.mlx_ptr);
}
