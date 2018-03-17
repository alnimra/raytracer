/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:03:03 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 14:03:03 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RTV1_H
# define _RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <time.h>
# define WIDTH  600
# define HEIGHT 600
typedef double v4sd __attribute__ ((vector_size (3 * sizeof(double))));
typedef struct		s_gl
{
	void	*lib;
	void	*surf;
	double live_trans[5];
}					t_gl;
t_gl				*create_gl(void *lib, void *surf);
typedef struct		s_canvas
{
	void	*img;
	char	*pix_data;
	int		size_line;
	int		byte_size;
	int		endian;
}					t_canvas;
t_canvas		*create_canvas(t_gl *gl);
typedef struct		s_params
{
	void *p1;
	void *p2;
	void *p3;
}					t_params;
typedef struct		t_inputs
{
	int	p_mouse_pos[2];
	int shift_key;
}					t_inputs;

typedef struct		s_3dpt
{
	v4sd	coord;
}					t_3dpt;
t_3dpt *create_3dpt(double x, double y, double z);
void    set3dpt(t_3dpt *pt, double x, double y, double z);
double get_x(t_3dpt *pt);
double get_y(t_3dpt *pt);
double get_z(t_3dpt *pt);
double mag(t_3dpt *pt);
t_3dpt *normal(t_3dpt *pt);
t_3dpt *multi(t_3dpt *pt, double scalar);
double dot(t_3dpt *pt1, t_3dpt *pt2);
t_3dpt *cross(t_3dpt *pt1, t_3dpt *pt2);
t_3dpt *add(t_3dpt *pt1, t_3dpt *pt2);
t_3dpt *sub(t_3dpt *pt1, t_3dpt *pt2);
typedef struct		s_vec
{
	t_3dpt	*comp[2];
}					t_vec;
t_vec *create_vec(t_3dpt *org, t_3dpt *dir);
void    set_vec(t_vec *v, double org[3], double dir[3]);
t_3dpt	*get_org(t_vec *v);
t_3dpt	*get_dir(t_vec *v);
typedef struct		s_cam
{
	t_3dpt	*prop[4];
}					t_cam;
t_cam *create_cam(t_3dpt *org, t_3dpt *dir, t_3dpt *right, t_3dpt *down);
void    set_cam(t_cam *cam, double org_and_dir[3], double right[3], double down[3]);
t_3dpt	*get_camorg(t_cam *cam);
t_3dpt	*get_camdir(t_cam *cam);
t_3dpt	*get_right(t_cam *cam);
t_3dpt	*get_down(t_cam *cam);
typedef struct		s_color
{
	double prop[4];
}					t_color;
t_color *create_color(double r, double g, double b, double special);
t_color *color_multi(t_color *color, double scalar);
t_color *add_col(t_color *color1, t_color *color2);
t_color *multi_col(t_color *color1, t_color *color2);
t_color *avg_col(t_color *color1, t_color *color2);
typedef struct		s_light
{
	t_3dpt	*org;
	t_color	*col;
}					t_light;
t_light *create_light(t_3dpt *org, t_color *col);
typedef struct		s_sphere
{
	t_3dpt	*cnt;
	double	rad;
	t_color	*col;
	double (*find_insct)(struct s_sphere*, t_vec*);
}					t_sphere;
t_sphere *create_sphere(t_3dpt *cnt, double rad, t_color *col);
t_3dpt *sphere_get_normal_at(t_sphere *sphere, t_3dpt *pt);
typedef struct		s_plane
{
	t_3dpt	*normal;
	double	dist;
	t_color	*col;
	double (*find_insct)(struct s_plane*, t_vec*);
}					t_plane;
t_plane *create_plane(t_3dpt *normal, double dist, t_color *col);
typedef struct		s_obj
{
	void *obj;
	char *type;
}					t_obj;
t_obj *create_obj(void *obj, char *type);
void store_pix(t_canvas *canvas, int x, int y, unsigned int c);
void store_color_pix(t_canvas *canvas, int x, int y, t_color *color);
void scenify(t_gl *gl, t_canvas *canvas);
#endif
