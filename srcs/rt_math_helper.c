/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 20:24:58 by mray              #+#    #+#             */
/*   Updated: 2018/03/25 20:24:58 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_visi_obj(char *str)
{
	return (ft_strcmp(str, "sphere") == 0 || ft_strcmp(str, "plane") == 0 ||
			ft_strcmp(str, "cyl") == 0 || ft_strcmp(str, "cone") == 0);
}

int		get_num_of_visi_objs(t_gl *gl)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (gl->obj_data[i])
	{
		if (is_visi_obj(gl->obj_data[i]->type))
			count++;
		i++;
	}
	return (count);
}

int		get_num_of_lights(t_gl *gl)
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

int		get_winning_obj(double *intersections, int size)
{
	int		i;
	int		i_min;
	double	max;

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

double	find_inscts(t_obj **objs, int i, t_vec *v)
{
	if (ft_strcmp(objs[i]->type, "sphere") == 0)
	{
		return (((t_sphere *)objs[i]->obj)
		->find_insct((t_sphere *)objs[i]->obj, v));
	}
	if (ft_strcmp(objs[i]->type, "plane") == 0)
	{
		return (((t_plane *)objs[i]->obj)->find_insct((t_plane *)objs[i]->obj,
		v));
	}
	if (ft_strcmp(objs[i]->type, "cyl") == 0)
		return (((t_cyl *)objs[i]->obj)->find_insct((t_cyl *)objs[i]->obj, v));
	if (ft_strcmp(objs[i]->type, "cone") == 0)
	{
		return (((t_cone *)objs[i]->obj)->find_insct((t_cone *)objs[i]->obj,
		v));
	}
	return (0.0);
}
