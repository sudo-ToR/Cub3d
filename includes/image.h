/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:18:41 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/08 19:52:30 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H


t_img			*create_new_img(t_mlx *m, t_img *ptr, int width, int height);
void			draw_pixel(t_img *ref, t_pos pos, unsigned char color[3], t_mlx m);
void			draw_pixel_hex(t_img *ref, t_pos pos, unsigned int hexcolor, t_mlx m);
void			draw_square(t_mlx m, t_img *ptr, int i, int j, unsigned int color, int width);
void			minimap(t_mlx *m, double cam_angle);
int				draw_minimap(t_mlx m);
void			draw_column(double distance, t_mlx *m, int column_nbr, char wall);

double			check_vert(t_mlx *m, double coeff, int dec);
double			check_hor(t_mlx *m, double coeff, int dec);
double			get_distance(double angle, t_mlx *m, char *wall);
void			draw_image(double cam_angle, t_mlx *m);
t_img			*create_text(t_mlx *m, t_img *text, char *path);

void			adjust_cam_angle(double *angle);
#endif