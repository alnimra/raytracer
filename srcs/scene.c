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
#include <stdio.h>

int get_winning_obj(double *intersections, int size)
{
	int	i;
	int	i_min;
	double max;

	i = -1;
	max = 0;
	while (++i < size)
	{
		if (max < intersections[i])
			max = intersections[i];
	}
	if (max > 0)
	{
		i = -1;
		while (++i < size)
		{
			if (intersections[i] > 0 && intersections[i] <= max)
			{
				max = intersections[i];
				i_min = i;
			}
		}
		return (i_min);
	}
	return (-1);
}

double find_inscts(t_obj **objs, int i, t_vec *v)
{
	if (ft_strcmp(objs[i]->type, "sphere") == 0)
		return (((t_sphere *)objs[i]->obj)
					->find_insct((t_sphere *)objs[i]->obj, v));
	if (ft_strcmp(objs[i]->type, "plane") == 0)
		return (
			((t_plane *)objs[i]->obj)->find_insct((t_plane *)objs[i]->obj, v));
	if (ft_strcmp(objs[i]->type, "cyl") == 0)
		return (((t_cyl *)objs[i]->obj)->find_insct((t_cyl *)objs[i]->obj, v));
	if (ft_strcmp(objs[i]->type, "cone") == 0)
		return (
			((t_cone *)objs[i]->obj)->find_insct((t_cone *)objs[i]->obj, v));
	return (0.0);
}

t_color get_color(t_obj **objs, int i)
{
	if (ft_strcmp(objs[i]->type, "sphere") == 0)
		return (((t_sphere *)objs[i]->obj)->col);
	if (ft_strcmp(objs[i]->type, "plane") == 0)
		return (((t_plane *)objs[i]->obj)->col);
	if (ft_strcmp(objs[i]->type, "cyl") == 0)
		return (((t_cyl *)objs[i]->obj)->col);
	if (ft_strcmp(objs[i]->type, "cone") == 0)
		return (((t_cone *)objs[i]->obj)->col);
	return ((t_color){0, 0, 0, 0});
}

t_3dpt get_normal_at(t_obj **objs, int i, t_3dpt pt)
{
	if (ft_strcmp(objs[i]->type, "sphere") == 0)
		return (sphere_get_normal_at((t_sphere *)objs[i]->obj, pt));
	else if (ft_strcmp(objs[i]->type, "plane") == 0)
		return (((t_plane *)objs[i]->obj)->normal);
	else if (ft_strcmp(objs[i]->type, "cyl") == 0)
		return (cyl_get_normal_at((t_cyl *)objs[i]->obj, pt));
	else if (ft_strcmp(objs[i]->type, "cone") == 0)
		return (cone_get_normal_at((t_cone *)objs[i]->obj, pt));
	return ((t_3dpt){0, 0, 0});
}

t_color get_color_at(t_3dpt insct_pos, t_3dpt insct_dir, t_obj **objs,
					 int winning_obj, t_light **light_sources, double accuracy,
					 double ambient_light, int num_of_objs)
{
	int		i;
	t_color winning_obj_color;
	t_3dpt  winning_obj_normal;
	t_3dpt  light_direction;
	t_color rendered_color;
	i = 0;
	winning_obj_color = get_color(objs, winning_obj);
	winning_obj_normal = get_normal_at(objs, winning_obj, insct_pos);
	rendered_color = col_multi(winning_obj_color, ambient_light);
	while (light_sources[i])
	{
		light_direction =
			normal(add(light_sources[i]->org, multi(insct_pos, -1)));
		double cos_angle = dot(winning_obj_normal, light_direction);
		if (cos_angle > 0)
		{
			int	shadowed = 0;
			t_3dpt dist_to_light =
				normal(add(light_sources[i]->org, multi(insct_pos, -1)));
			double dist_to_light_mag = mag(dist_to_light);
			t_vec *shadow_vec = create_vec(
				insct_pos,
				normal(add(light_sources[i]->org, multi(insct_pos, -1))));
			int obj_i = -1;
			// need to make num of objects;
			double intersections_2[num_of_objs];
			while (objs[++obj_i] && !shadowed)
				intersections_2[obj_i] = find_inscts(objs, obj_i, shadow_vec);
			obj_i = 0;
			while (objs[obj_i])
			{
				if (intersections_2[obj_i] > accuracy)
				{
					if (intersections_2[obj_i] <= dist_to_light_mag)
						shadowed = 1;
					break;
				}
				obj_i++;
			}
			if (shadowed == 0)
			{
				rendered_color = add_col(
					rendered_color, col_multi(multi_col(winning_obj_color,
														light_sources[i]->col),
											  cos_angle));
				// Apply shine
				// ft_putstr("here");
				// exit(1);
				if (winning_obj_color[3] > 0 && winning_obj_color[3] <= 1)
				{
					// Special 0-1
					double dot1 = dot(multi(winning_obj_normal, -1),
									  multi(insct_dir, -1));
					t_3dpt scalar1 = multi(winning_obj_normal, dot1);
					t_3dpt add1 = add(scalar1, insct_dir);
					t_3dpt scalar2 = multi(add1, 2);
					t_3dpt add2 = add(multi(insct_dir, -1), scalar2);
					t_3dpt reflection_dir = normal(add2);

					double specular = dot(reflection_dir, light_direction);
					if (specular > 0)
					{
						specular = pow(specular, 10);
						rendered_color =
							add_col(rendered_color,
									col_multi(light_sources[i]->col,
											  specular * winning_obj_color[3]));
					}
				}
			}
		}
		i++;
	}
	correct_color_leaks(&rendered_color);
	return rendered_color;
}
int get_num_of_visi_objs(t_gl *gl)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (gl->obj_data[i])
	{
		if (ft_strcmp(gl->obj_data[i]->type, "sphere") == 0 ||
			ft_strcmp(gl->obj_data[i]->type, "plane") == 0 ||
			ft_strcmp(gl->obj_data[i]->type, "cyl") == 0 ||
			ft_strcmp(gl->obj_data[i]->type, "cone") == 0)
			count++;
		i++;
	}
	return (count);
}

int get_num_of_lights(t_gl *gl)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (gl->obj_data[i])
	{
		if (ft_strcmp(gl->obj_data[i]->type, "light") == 0)
			count++;
		i++;
	}
	return (count);
}

void init_objs(t_gl *gl, t_obj ***objs_place, t_light ***lights, t_cam **cam)
{
	int i;
	int j;
	int k;
	int num_of_visi_objs;
	int num_of_lights;

	num_of_visi_objs = get_num_of_visi_objs(gl);
	num_of_lights = get_num_of_lights(gl);
	*objs_place =
		(t_obj **)ft_memalloc(sizeof(t_obj *) * (num_of_visi_objs + 1));
	ft_putnbr(num_of_visi_objs);
	*lights = (t_light **)ft_memalloc(sizeof(t_light *) * (num_of_lights + 1));
	i = 0;
	j = 0;
	k = 0;
	while (gl->obj_data[i])
	{
		if (ft_strcmp(gl->obj_data[i]->type, "light") == 0)
		{
			(*lights)[k] = (t_light *)gl->obj_data[i]->obj;
			k++;
		}
		else if (ft_strcmp(gl->obj_data[i]->type, "cam") == 0)
		{
			*cam = (t_cam *)gl->obj_data[i]->obj;
			(*cam)->prop[2] =
				normal(cross(create_3dpt(0, 1, 0), (*cam)->prop[1]));
			(*cam)->prop[3] = cross((*cam)->prop[2], (*cam)->prop[1]);
		}
		else if (ft_strcmp(gl->obj_data[i]->type, "sphere") == 0 ||
				 ft_strcmp(gl->obj_data[i]->type, "plane") == 0 ||
				 ft_strcmp(gl->obj_data[i]->type, "cyl") == 0 ||
				 ft_strcmp(gl->obj_data[i]->type, "cone") == 0)
		{
			((*objs_place)[j]) = gl->obj_data[i];
			j++;
		}
		i++;
	}
}

void scenify(t_gl *gl, t_canvas *canvas)
{
	int x;
	int y;
	// t_3dpt *o_a;
	t_cam *   cam;
	t_vec *   cam_vec;
	double	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	double	ambient_light = 0.2;
	double	accuracy = 0.00000001;
	double	xamnt;
	double	yamnt;
	t_3dpt	cam_vec_dir;
	int		  intersection_i;
	int		  num_of_visi_objs;
	double *  intersections;
	int		  winning_obj;
	t_obj **  objs;
	t_light **lights;
	ft_putendl("HERE");
	num_of_visi_objs = get_num_of_visi_objs(gl);
	init_objs(gl, &objs, &lights, &cam);
	y = -1;
	cam_vec = create_vec(create_3dpt(0, 0, 0), create_3dpt(0, 0, 0));
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			intersections =
				(double *)ft_memalloc(sizeof(double) * num_of_visi_objs);
			if (WIDTH > HEIGHT)
			{
				xamnt = ((x + 0.5) / WIDTH * aspect_ratio -
						 (((WIDTH - HEIGHT) / (double)HEIGHT) / 2));
				yamnt = ((HEIGHT - y) + 0.5) / HEIGHT;
			}
			else if (HEIGHT > WIDTH)
			{
				xamnt = (x + 0.5) / WIDTH;
				yamnt = (((HEIGHT - y) + 0.5) / HEIGHT) / aspect_ratio -
						(((HEIGHT - WIDTH) / (double)WIDTH) / 2);
			}
			else
			{
				xamnt = (x + 0.5) / WIDTH;
				yamnt = ((HEIGHT - y) + 0.5) / HEIGHT;
			}
			cam_vec_dir = normal(
				add(cam->prop[1], add(multi(cam->prop[2], xamnt - 0.5),
									  multi(cam->prop[3], yamnt - 0.5))));
			set_vec(cam_vec, cam->prop[0], cam_vec_dir);
			intersection_i = 0;
			while (objs[intersection_i])
			{
				intersections[intersection_i] =
					find_inscts(objs, intersection_i, cam_vec);
				intersection_i++;
			}
			winning_obj = get_winning_obj(intersections, num_of_visi_objs);
			if (winning_obj == -1)
				store_pix(canvas, x, y, 0);
			else
			{
				t_3dpt insct_pos =
					add(cam_vec->comp[0],
						multi(cam_vec->comp[1], intersections[winning_obj]));
				t_3dpt insct_dir = cam_vec->comp[1];
				store_color_pix(canvas, x, y,
								get_color_at(insct_pos, insct_dir, objs,
											 winning_obj, lights, accuracy,
											 ambient_light, num_of_visi_objs));
			}
			free(intersections);
			// printf("%d", winning_obj);
		}
	}
	free(cam_vec);
	free(cam);
	free(lights);
	free(objs);
	mlx_put_image_to_window(gl->lib, gl->surf, canvas->img, 0, 0);
}
