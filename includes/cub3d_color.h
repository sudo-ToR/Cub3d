#ifndef CUB3D_COLOR_H
#define CUB3D_COLOR_H

typedef struct	s_color
{
	UCHAR r;
	UCHAR g;
	UCHAR b;
	UCHAR a;
}				t_color;

t_color		create_color(UCHAR r, UCHAR g, UCHAR b, UCHAR a);
t_color		*malloc_color(UCHAR r, UCHAR g, UCHAR b, UCHAR a);
void 		destroy_color(t_color to_destroy);
void 		free_color(t_color *to_free);

#endif
