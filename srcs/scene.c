/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:14:14 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 12:14:14 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_objs(t_gl *gl)
{
	int ints[3];
	int num_of_l;

	gl->num_of_visi_objs = get_num_of_visi_objs(gl);
	num_of_l = get_num_of_lights(gl);
	gl->objs =
		(t_obj **)ft_memalloc(sizeof(t_obj *) * (gl->num_of_visi_objs + 1));
	gl->lights = (t_light **)ft_memalloc(sizeof(t_light *) * (num_of_l + 1));
	ints[0] = -1;
	ints[1] = 0;
	ints[2] = 0;
	while (gl->obj_data[++ints[0]])
	{
		if (ft_strcmp(gl->obj_data[ints[0]]->type, "light") == 0)
			gl->lights[ints[2]++] = (t_light *)gl->obj_data[ints[0]]->obj;
		else if (ft_strcmp(gl->obj_data[ints[0]]->type, "cam") == 0)
		{
			gl->cam = (t_cam *)gl->obj_data[ints[0]]->obj;
			(gl->cam)->prop[2] =
				normal(cross(create_3dpt(0, 1, 0), (gl->cam)->prop[1]));
			(gl->cam)->prop[3] = cross((gl->cam)->prop[2], (gl->cam)->prop[1]);
		}
		else if (is_visi_obj(gl->obj_data[ints[0]]->type))
			((gl->objs)[ints[1]++]) = gl->obj_data[ints[0]];
	}
}

void	init_screen_offsets(t_gl *gl, int x, int y)
{
	if (WIDTH > HEIGHT)
	{
		gl->x_offset = ((x + 0.5) / WIDTH * gl->aspect_ratio -
					(((WIDTH - HEIGHT) / (double)HEIGHT) / 2));
		gl->y_offset = ((HEIGHT - y) + 0.5) / HEIGHT;
	}
	else if (HEIGHT > WIDTH)
	{
		gl->x_offset = (x + 0.5) / WIDTH;
		gl->y_offset = (((HEIGHT - y) + 0.5) / HEIGHT) / gl->aspect_ratio -
				(((HEIGHT - WIDTH) / (double)WIDTH) / 2);
	}
	else
	{
		gl->x_offset = (x + 0.5) / WIDTH;
		gl->y_offset = ((HEIGHT - y) + 0.5) / HEIGHT;
	}
}

void	shoot_vector_and_calc_rt_magic(t_gl *gl, t_canvas *canvas, int x, int y)
{
	t_vec	*cam_vec;
	t_3dpt	cam_vec_dir;
	double	inters[gl->num_of_visi_objs];
	int		intersection_i;

	cam_vec = create_vec(create_3dpt(0, 0, 0), create_3dpt(0, 0, 0));
	cam_vec_dir = normal(add(gl->cam->prop[1],
							add(multi(gl->cam->prop[2], gl->x_offset - 0.5),
								multi(gl->cam->prop[3], gl->y_offset - 0.5))));
	set_vec(cam_vec, gl->cam->prop[0], cam_vec_dir);
	intersection_i = -1;
	while (gl->objs[++intersection_i])
		inters[intersection_i] = find_inscts(gl->objs, intersection_i, cam_vec);
	gl->winning_obj = get_winning_obj(inters, gl->num_of_visi_objs);
	if (gl->winning_obj == -1)
		store_pix(canvas, x, y, 0);
	else
	{
		gl->insct_pos = add(cam_vec->comp[0],
							multi(cam_vec->comp[1], inters[gl->winning_obj]));
		gl->insct_dir = cam_vec->comp[1];
		store_color_pix(canvas, x, y, get_color_at(gl));
	}
	ft_memdel((void **)&cam_vec);
}

void	scenify(t_gl *gl, t_canvas *canvas)
{
	int x;
	int y;

	gl->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	gl->ambient_light = 0.2;
	gl->accuracy = 0.00000001;
	gl->num_of_visi_objs = get_num_of_visi_objs(gl);
	init_objs(gl);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			init_screen_offsets(gl, x, y);
			shoot_vector_and_calc_rt_magic(gl, canvas, x, y);
		}
	}
	ft_memdel((void **)&gl->cam);
	free_array((void **)gl->lights);
	free(gl->objs);
	mlx_put_image_to_window(gl->lib, gl->surf, canvas->img, 0, 0);
}
