/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:15:56 by user42            #+#    #+#             */
/*   Updated: 2020/04/21 12:12:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*create_text(t_mlx *m, t_img *text, char *path)
{
	if (!(text->ref = mlx_xpm_file_to_image(m->mlx_ptr, path, &text->w,
		&text->h)))
		return (NULL);
	if (!(text->img = (mlx_get_data_addr(text->ref, &text->bits_per_pixel,
		&text->size_line, &text->endian))))
		return (NULL);
	return (text);
}

char	*get_pixel_texture(t_img *texture, t_pos coord)
{
	int				index;

	index = texture->size_line * coord.y + texture->bits_per_pixel
	/ 8 * coord.x;
	return (&texture->img[index]);
}

void	select_texture(t_img **texture, t_mlx *m)
{
	if (!m->ray.dir_wall)
	{
		if (m->ray_angle >= 0 && m->ray_angle <= M_PI)
			*texture = &m->no_text;
		else
			*texture = &m->so_text;
	}
	else
	{
		if (m->ray_angle >= M_PI_2 && m->ray_angle <= 3. * M_PI_2)
			*texture = &m->we_text;
		else
			*texture = &m->ea_text;
	}
}
