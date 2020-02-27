/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:40:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/27 17:45:00 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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