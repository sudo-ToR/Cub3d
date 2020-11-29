/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:43:35 by user42            #+#    #+#             */
/*   Updated: 2020/11/29 18:01:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_cam_angle(double *angle)
{
	if (*angle > 2.0 * M_PI)
		*angle -= 2.0 * M_PI;
	if (*angle < 0.)
		*angle += 2.0 * M_PI;
}

void	free_struct(t_mlx *m)
{
	free(m->p.r);
	free(m->p.ea);
	free(m->p.no);
	free(m->p.so);
	free(m->p.we);
	free(m->p.s);
	free(m->p.map);
}

int		exit_game(t_mlx *m)
{
	mlx_destroy_window(m->mlx_ptr, m->win_ptr);
	m->win_ptr = NULL;
	mlx_destroy_image(m->mlx_ptr, m->minimap.ref);
	mlx_destroy_image(m->mlx_ptr, m->render.ref);
	mlx_destroy_image(m->mlx_ptr, m->no_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->so_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->ea_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->we_text.ref);
	mlx_destroy_image(m->mlx_ptr, m->s_text.ref);
	free(m->mlx_ptr);
	free_struct(m);
	exit(0);
}
