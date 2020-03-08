/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:50:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/08 19:59:16 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>

double		check_vert(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	if (dec == 1)
		coord.x = floor(m->pl.x + dec) - m->pl.x + 0.000001;
	else
		coord.x = -((double)((double)m->pl.x - floor(m->pl.x)) + 0.000001);
	coord.y = coeff * coord.x;
	while (coord.x + m->pl.x < (double)m->p.width && coord.y + m->pl.y < (double)m->p.height)
	{
		if (coord.y + m->pl.y < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			draw_pixel_hex(&m->minimap, (t_pos){(coord.x  + m->pl.x) * 16, (coord.y + m->pl.y) * 16}, 0xffff0000, *m);
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

	if (dec == 1)
		coord.y = floor(m->pl.y + dec) - m->pl.y + 0.000001;
	else
		coord.y = (((double)((double)m->pl.y - floor(m->pl.y)) + 0.000001) * (double)dec);
	coord.x = coord.y / coeff;
	while (coord.y + m->pl.y < (double)m->p.height && coord.x + m->pl.x < (double)m->p.width)
	{
		if (coord.x + m->pl.x < 0. || coeff == 1.)
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

	if (cam_angle < M_PI / 6.0)
		cam_angle += 2.0 * M_PI;
	angle = - (M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3 / m->p.r[0];
	i = 0;
	while (angle <= M_PI / 6. + cam_angle && i < m->p.r[0])
	{
		adjust_cam_angle(&angle);
		distance = get_distance(angle, m, &wall);
		draw_column(distance, m, i, wall);
		angle += var_angle;
		i++;
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
	inc.x = (angle >= M_PI_2 && angle <= 3. * M_PI_2) ? -1 : 1;
	inc.y = (angle >= M_PI && angle <= 2. * M_PI) ? -1 : 1;
	distance.x = check_vert(m, coeff, inc.x) * cos(m->cam_angle - angle);
	distance.y = check_hor(m, coeff, inc.y) * cos(m->cam_angle - angle);
	*wall = (distance.x > distance.y) ? 'H' : 'V';
	return (fmin(distance.x, distance.y));
}
