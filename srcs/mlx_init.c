/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 10:18:22 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/25 21:53:47 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char
	get_map_pos(t_mlx m, int x, int y)
{
	// printf("%d %d (max %d %d)\n", x, y, m.p.height, m.p.width);
	return (m.p.map[y][x]);
}

void
	draw_pixel(t_img *ref, t_pos pos, unsigned char color[3], t_mlx m)
{
	int calcul;
	unsigned int c;
	
	calcul = (pos.y - 1) * ref->w + (pos.x - 1);
	c = (0 << 24) | (color[0] << 16) | (color[1] << 8) | (color[2]);
	((unsigned int *)ref->img)[calcul] = c;
}

void
	draw_pixel_hex(t_img *ref, t_pos pos, unsigned int hexcolor, t_mlx m)
{
	int calcul;

	calcul = (pos.y) * ref->w + pos.x;
	((unsigned int *)ref->img)[calcul] = hexcolor;
}


void
	draw_square(t_mlx m, t_img *ptr, int i, int j, unsigned int color, int width)
{
	t_pos square;

	square.y = i;

	while (square.y < i + width)
	{

		square.x = j;
		while (square.x < j + width)
		{
			draw_pixel_hex(ptr, square, color, m);
			square.x++;
		}
		square.y++;
	}
}

int
	check_vert(t_mlx m, double coeff, int dec)
{
	int x;

	x = 0;
	while (x < m.p.width && coeff * x < m.p.height)
	{
		if (m.p.map[(int)((x * coeff) + m.pl.y)][(int)(x + m.pl.x)] == '1')
		{
			draw_square(m, &m.minimap, x * coeff + m.pl.y, x+ m.pl.x, 0xffff00, 4);
			return (x);
		}
		x += dec;
	}
	return (-1);
}

int nothing() {}

int
	check_hor(t_mlx m, double coeff, int dec)
{
	int y;
	t_pos	pos;

	y = 0;
	while (y < m.p.height && y / coeff < m.p.width && y + m.pl.y > 0 && y / coeff + m.pl.x > 0)
	{
		printf("x = %d\t y = %d\n", (int)((y / coeff) + m.pl.x), (int)(y + m.pl.y));
		if (m.p.map[(int)(y + m.pl.y)][(int)((y / coeff) + m.pl.x)] == '1')
		{
			pos.x = y / coeff + m.pl.x;
			pos.y = y + m.pl.y;
			// draw_square(m, &m.minimap, pos.y, pos.x,0xffff00, 4);
			return (y);
		}
		y += dec;
	}
	return (-1);	
}


double
	get_distance(double angle, t_mlx m)
{
	double		coeff;
	t_pos_fl	distance;
	t_pos		inc;
	t_pos		coord;

	coord = (t_pos) {0};
	// coeff = (tan(angle) == 0) ? 0 : 1 / tan(angle);
	coeff = 1;
	// printf("coeff = %f\tangle = %f\n", coeff, angle * 180 / M_PI);
	inc.x = (angle >= M_PI_2 && angle < 3 * M_PI_2) ? 1 : -1;
	inc.y = (angle >= 0 && angle <= M_PI) ? 1 : -1;
	distance.x = check_vert(m, coeff, inc.x);
	if (coeff == 0)
		return(distance.x);
	distance.y = check_hor(m, coeff, inc.y);
	return (fmin(distance.x, distance.y));
}

void
	draw_column(double distance, t_mlx m, int column_nbr)
{
	double				heigth;
	int					i;
	unsigned char		color[3];
	unsigned char		floor_color[3];
	unsigned char		ceil_color[3];
	t_pos_fl			pos;
	t_pos				pixel;
	
	heigth =  (double)m.p.r[1] / distance;
	color[0] = 255;
	color[1] = 255;
	color[2] = 255;
	ceil_color[0] = 0;
	ceil_color[1] = 0;
	ceil_color[2] = 255;
	floor_color[0] = 255;
	floor_color[1] = 0;
	floor_color[2] = 0;
	i = 0;
	pixel.x = floor(m.po.x) + column_nbr;
	pos.y = 0;
	while (pos.y < m.p.r[1])
	{
		pixel.y = (int)floor(pos.y);
		if (pos.y < ((double)(m.p.r[1] / 2)) - (heigth / 2))
			draw_pixel(&m.render, pixel, ceil_color, m);
		else if (pos.y <= (m.p.r[1] / 2) + (heigth / 2) && pos.y >= ((double)(m.p.r[1] / 2)) - (heigth / 2))
			draw_pixel(&m.render, pixel, color, m);
		else if (pos.y > (m.p.r[1] / 2) + (heigth / 2))
		 	draw_pixel(&m.render, pixel, floor_color, m);
		pos.y++;
	}
}

void
	get_image(double cam_angle, t_mlx m)
{
	double	angle;
	int		i;
	double	var_angle;
	double	distance;

	angle = - (M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3 / m.p.r[0];
	i = 0;
	while (angle <= M_PI / 6 + cam_angle && i++ < m.p.r[0])
	{
		distance = get_distance(angle, m);
		// distance = 3.5;
		// printf("angle = %f\tdstance = %f\n", angle, distance);
		draw_column(abs(distance), m, i);
		angle += var_angle;
	}
}

void
	get_initial_position(char *v, t_pars p, t_pos_fl *pl)
{
	int		i;
	int		j;

	i = 0;
	while (i < p.height)
	{
		j = 0;
		while (p.map[i][j])
		{
			if (p.map[i][j] == 'N' || p.map[i][j] == 'S' || p.map[i][j] == 'W'
				|| p.map[i][j] == 'E')
			{
				*v = p.map[i][j];
				pl->x = (double)j + 0.5;
				pl->y = (double)i + 0.5;
				p.map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void
	init_dir_vector(char v, double *cam_angle)
{
	if (v == 'S')
		*cam_angle = M_PI_2;
	else if (v == 'N')
		*cam_angle = 3 * M_PI_2;
	else if (v == 'E')
		*cam_angle = 0;
	else if (v == 'W')
		*cam_angle = M_PI;
}

void
	minimap(t_mlx m, double cam_angle)
{
	int i;
	int j;

	i = 0;
	while (i < m.p.height)
	{
		j = 0;
		while (m.p.map[i][j])
		{
			if (m.p.map[i][j] == '1')
				draw_square(m, &m.minimap, i * 16, j * 16, 0xff0000, 16);
			j++;
		}
		i++;
	}
	t_pos_fl player_pos;
	player_pos = (t_pos_fl) {
		.x = (double)m.pl.x * 16,
		.y = (double)m.pl.y * 16.
	};
	// printf("Player is at pos %.2f %.2f\n", (double)m.pl.x, (double)m.pl.y);
	draw_square(m, &m.minimap, (int)(player_pos.y - 3.), (int)(player_pos.x - 3.), 0x00ff0000, 6);
}

void
	ft_init_mlx(t_mlx m)
{
	char	v;
	double	cam_angle;

	get_initial_position(&v, m.p, &m.pl);
	init_dir_vector(v, &cam_angle);
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
