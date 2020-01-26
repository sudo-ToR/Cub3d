#ifndef CUB3D_VECTOR_H
#define CUB3D_VECTOR_H

typedef struct s_vector2
{
	int x;
	int y;
}				t_vector2;

t_vector2 create_vector2(int x, int y);
t_vector2 *malloc_vector2(int x, int y);
void destroy_vector2(t_vector2 to_delete);
void free_vector2(t_vector2 *to_free);

#endif
