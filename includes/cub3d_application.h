#ifndef CUB3D_APPLICATION_H
#define CUB3D_APPLICATION_H

#include "cub3d_color.h"
#include "cub3d_vector.h"

typedef struct	s_application
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;

	t_vector2 size;

	t_color background;

	char *pixels;
	int bits_per_pixel;
	int size_line;
	int endian;
}				t_application;

extern t_application g_app;

void create_application(t_vector2 size, char *prog_name);
void destroy_application();

void put_pixel(t_vector2 pos, t_color color);
void clear_screen();
void render_screen();
int run_application();

#endif
