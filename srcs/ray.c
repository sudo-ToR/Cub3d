/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:50:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/04 11:55:08 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>

double		check_vert(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.x = (((double)((double)m->pl.x - (int)m->pl.x) + 0.000001) * (double)dec);
	if (dec == 1)
		coord.x = (int)(m->pl.x + dec) - m->pl.x + 0.000001;
	coord.y = coeff * coord.x;
	// printf("x = %f\tcoord.y = %f\tdiff = %f===>%f\n", m->pl.x, coord.y, coord.x, coord.x + m->pl.x);
	while (coord.x + m->pl.x < m->p.width && coord.y + m->pl.y < m->p.height)
	{
		if (coord.y + m->pl.y < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			draw_pixel_hex(&m->minimap, (t_pos){(coord.x  + m->pl.x) * 16, (coord.y + m->pl.y) * 16}, 0xffff0000, *m);
			return (sqrt(pow(coord.y, 2) + pow((double)coord.x, 2)));
		}
		coord.x += dec;
		coord.y = coeff * coord.x;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

double		check_hor(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.y = (((double)((double)m->pl.y - (int)m->pl.y) + 0.000001) * (double)dec);
	coord.x = coord.y / coeff;
	printf("anle = %f\tcoeff = %f\tx = %f\n", m->cam_angle, coeff, coord.x);
	while (coord.y + m->pl.y < m->p.height && coord.x + m->pl.x < m->p.width)
	{
		if (coord.x + m->pl.x < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
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

	angle = - (M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3 / m->p.r[0];
	i = 0;
	while (angle <= M_PI / 6 + cam_angle && i++ < m->p.r[0])
	{
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

	coord = (t_pos) {0};
	coeff =  tan(angle);
	inc.x = (angle >= M_PI_2 && angle <= 3 * M_PI_2) ? -1 : 1;
	inc.y = (angle >= 0 && angle <= M_PI) ? 1 : -1;
	distance.x = check_vert(m, coeff, inc.x) * cos(m->cam_angle - angle);
	if (angle == 0 || angle == M_PI || angle == M_PI_2 || angle == 3 * M_PI_2)
	{
		*wall = (!angle || angle == M_PI) ? 'V' : 'H';
		return(!angle || angle == M_PI) ? distance.x : check_hor(m, coeff, inc.y);
	}
	distance.y = check_hor(m, coeff, inc.y) * cos(m->cam_angle - angle);
	*wall = (distance.x > distance.y) ? 'H' : 'V';
	return (fmin(distance.x, distance.y));
}
