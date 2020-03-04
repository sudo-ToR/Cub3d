/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:50:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/04 22:47:00 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>

double		check_vert(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.x = (((double)((double)m->pl.x - floor(m->pl.x)) + 0.000001) * (double)dec);
	if (dec == 1)
		coord.x = floor(m->pl.x + dec) - m->pl.x + 0.000001;
	coord.y = coeff * coord.x;
	while (coord.x + m->pl.x < (double)m->p.width && coord.y + m->pl.y < (double)m->p.height)
	{
		if (coord.y + m->pl.y < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			// printf("Vertical   =====> x = %d\ty = %d\tcoeff = %f\n", (int)(coord.y + m->pl.y), (int)(coord.x + m->pl.x), coeff);
			draw_pixel_hex(&m->minimap, (t_pos){(coord.x  + m->pl.x) * 16, (coord.y + m->pl.y) * 16}, 0xffff0000, *m);
			printf("distance x = %f\n", sqrt(pow(coord.y, 2) + pow((double)coord.x, 2)));
			return (sqrt(pow(coord.y, 2) + pow((double)coord.x, 2)));
		}
		coord.x += (double)dec;
		coord.y = coeff * coord.x;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

double		check_hor(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.y = (((double)((double)m->pl.y - floor(m->pl.y)) + 0.000001) * (double)dec);
	coord.x = coord.y / coeff;
	if (dec == 1)
		coord.y = floor(m->pl.y + dec) - m->pl.y + 0.000001;
	// printf("diff = %f\ty = %f\tdec = %d =======>%f\n", coord.y, m->pl.y, dec, m->pl.y + coord.y);
	while (coord.y + m->pl.y < (double)m->p.height && coord.x + m->pl.x < (double)m->p.width)
	{
		if (coord.x + m->pl.x < 0. || coeff == 1.)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			printf("Horizontal =====> x = %d\ty = %d\tcoeff = %f\n", (int)(coord.y + m->pl.y), (int)(coord.x + m->pl.x), coeff);
			draw_pixel_hex(&m->minimap, (t_pos){ (coord.x  + m->pl.x)* 16.0,  (coord.y + m->pl.y) * 16.0}, 0xffffffff, *m);
			return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
		}
		coord.y += dec;
		coord.x = coord.y / coeff;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

void		draw_image(double cam_angle, t_mlx *m)
{
	double	angle;
	int		i;
	double	var_angle;
	double	distance;
	char	wall;

	if (cam_angle < M_PI / 6.0)
		cam_angle += 2.0 * M_PI;
	angle = - (M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3 / m->p.r[0];
	i = 0;
	while (angle <= M_PI / 6 + cam_angle && i++ < m->p.r[0])
	{
		adjust_cam_angle(&angle);
		distance = get_distance(angle, m, &wall);
		draw_column(distance, m, i, wall);
		angle += var_angle;
	}
}

double		get_distance(double angle, t_mlx *m, char *wall)
{
	double		coeff;
	t_pos_fl	distance;
	t_pos		inc;
	t_pos		coord;

	coord = (t_pos) {0, 0};
	coeff =  tan(angle);
	inc.x = (angle >= M_PI_2 && angle <= 3 * M_PI_2) ? -1 : 1;
	inc.y = (angle >= M_PI && angle <= 2. * M_PI) ? -1 : 1;
	distance.x = check_vert(m, coeff, inc.x) * cos(m->cam_angle - angle);
	// if (angle == 0|| angle == M_PI || angle == M_PI_2 || angle == 3 * M_PI_2)
	// {
	// 	*wall = (!angle || angle == M_PI) ? 'V' : 'H';
	// 	return(!angle || angle == M_PI) ? distance.x : check_hor(m, coeff, inc.y);
	// }
	distance.y = check_hor(m, coeff, inc.y) * cos(m->cam_angle - angle);
	// printf("dist x = %f\tdist y  %f\t, angle = %f\n", distance.x, distance.y, angle * 180 / M_PI);
	*wall = (distance.x > distance.y) ? 'H' : 'V';
	return (fmin(distance.x, distance.y));
}
