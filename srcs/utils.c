/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:43:35 by user42            #+#    #+#             */
/*   Updated: 2020/12/29 20:56:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error_dupplication_text(char *line, char **text, t_mlx *m)
{
	if (clean_texture(line, text))
		return (aff_error(DUPLICATION_ARGUMENT, m));
	return (0);
}

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
	free(m->p.c);
	free(m->p.f);
	free_table(m->p.map);
	free(m->distance.distance);
}

int		check_img_add(void *img)
{
	if (img)
		return (0);
	return (1);
}

int		exit_game(t_mlx *m, int mode)
{
	if (!mode)
		mlx_destroy_window(m->mlx_ptr, m->win_ptr);
	if (!(check_img_add(m->minimap.ref)))
		mlx_destroy_image(m->mlx_ptr, m->minimap.ref);
	if (!(check_img_add(m->render.ref)))
		mlx_destroy_image(m->mlx_ptr, m->render.ref);
	if (!(check_img_add(m->no_text.ref)))
		mlx_destroy_image(m->mlx_ptr, m->no_text.ref);
	if (!(check_img_add(m->so_text.ref)))
		mlx_destroy_image(m->mlx_ptr, m->so_text.ref);
	if (!(check_img_add(m->ea_text.ref)))
		mlx_destroy_image(m->mlx_ptr, m->ea_text.ref);
	if (!(check_img_add(m->we_text.ref)))
		mlx_destroy_image(m->mlx_ptr, m->we_text.ref);
	if (!(check_img_add(m->s_text.ref)))
		mlx_destroy_image(m->mlx_ptr, m->s_text.ref);
	free(m->mlx_ptr);
	free_struct(m);
	exit(0);
}
