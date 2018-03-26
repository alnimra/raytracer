/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 20:27:06 by mray              #+#    #+#             */
/*   Updated: 2018/03/25 20:27:06 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		get_color(t_obj **objs, int i)
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

t_3dpt		get_normal_at(t_obj **objs, int i, t_3dpt pt)
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

void		determine_if_shadowed(t_gl *gl, int i)
{
	int		obj_i;
	double	intersections_2[gl->num_of_visi_objs];
	double	dist_to_light_mag;

	gl->shadowed = 0;
	dist_to_light_mag =
		mag(normal(add(gl->lights[i]->org, multi(gl->insct_pos, -1))));
	gl->shadow_vec =
		create_vec(gl->insct_pos,
				normal(add(gl->lights[i]->org, multi(gl->insct_pos, -1))));
	obj_i = -1;
	while (gl->objs[++obj_i] && !gl->shadowed)
		intersections_2[obj_i] = find_inscts(gl->objs, obj_i, gl->shadow_vec);
	obj_i = 0;
	while (gl->objs[obj_i])
	{
		if (intersections_2[obj_i] > gl->accuracy)
		{
			if (intersections_2[obj_i] <= dist_to_light_mag)
				gl->shadowed = 1;
			break ;
		}
		obj_i++;
	}
}

void		if_not_shadowed(t_gl *gl, t_color *rendered_color,
						t_3dpt *light_direction, int i)
{
	double specular;

	*rendered_color =
		add_col(*rendered_color,
				col_multi(multi_col(gl->winning_obj_color, gl->lights[i]->col),
						gl->cos_angle));
	if (gl->winning_obj_color[3] > 0 && gl->winning_obj_color[3] <= 1)
	{
		specular = dot(
			normal(add(multi(gl->insct_dir, -1),
					multi(add(multi(gl->winning_obj_normal,
									dot(multi(gl->winning_obj_normal, -1),
										multi(gl->insct_dir, -1))),
			gl->insct_dir),
						2))),
			*light_direction);
		if (specular > 0)
		{
			specular = pow(specular, 10);
			*rendered_color =
				add_col(*rendered_color,
						col_multi(gl->lights[i]->col,
							specular * gl->winning_obj_color[3]));
		}
	}
}

t_color		get_color_at(t_gl *gl)
{
	int		i;
	t_3dpt	light_direction;
	t_color	rendered_color;

	gl->winning_obj_color = get_color(gl->objs, gl->winning_obj);
	gl->winning_obj_normal =
		get_normal_at(gl->objs, gl->winning_obj, gl->insct_pos);
	rendered_color = col_multi(gl->winning_obj_color, gl->ambient_light);
	i = 0;
	while (gl->lights[i])
	{
		light_direction =
			normal(add(gl->lights[i]->org, multi(gl->insct_pos, -1)));
		gl->cos_angle = dot(gl->winning_obj_normal, light_direction);
		if (gl->cos_angle > 0)
		{
			determine_if_shadowed(gl, i);
			if (gl->shadowed == 0)
				if_not_shadowed(gl, &rendered_color, &light_direction, i);
			free(gl->shadow_vec);
		}
		i++;
	}
	correct_color_leaks(&rendered_color);
	return (rendered_color);
}
