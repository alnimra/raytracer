/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:18:19 by mray              #+#    #+#             */
/*   Updated: 2018/03/23 15:18:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double find_intersection_cone(t_cone *cone, t_vec *vec)
{
	double t[2];
	double coef[3];
	double disc;
	double roots[2];

	t[0] = sin(cone->tilt);
	t[1] = cos(cone->tilt);
	coef[0] =
		pow(t[1], 2) * squ(sub(vec->comp[1],
							   multi(cone->vec->comp[1],
									 dot(vec->comp[1], cone->vec->comp[1])))) -
		pow(t[0], 2) * dot(vec->comp[1], cone->vec->comp[1]) *
			dot(vec->comp[1], cone->vec->comp[1]);
	coef[1] =
		2 * pow(t[1], 2) *
			dot(sub(vec->comp[1], multi(cone->vec->comp[1],
										dot(vec->comp[1], cone->vec->comp[1]))),
				sub(sub(vec->comp[0], cone->vec->comp[0]),
					multi(cone->vec->comp[1],
						  dot(sub(vec->comp[0], cone->vec->comp[0]),
							  cone->vec->comp[1])))) -
		2 * pow(t[0], 2) * dot(vec->comp[1], cone->vec->comp[1]) *
			dot(sub(vec->comp[0], cone->vec->comp[0]), cone->vec->comp[1]);
	coef[2] =
		pow(t[1], 2) * squ(sub(sub(vec->comp[0], cone->vec->comp[0]),
							   multi(cone->vec->comp[1],
									 dot(sub(vec->comp[0], cone->vec->comp[0]),
										 cone->vec->comp[1])))) -
		pow(t[0], 2) *
			dot(sub(vec->comp[0], cone->vec->comp[0]), cone->vec->comp[1]) *
			dot(sub(vec->comp[0], cone->vec->comp[0]), cone->vec->comp[1]);
	disc = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (disc > 0)
	{
		roots[0] = ((-coef[1] - sqrt(disc)) / (2 * coef[0])) - 0.000001;
		if (roots[0] > 0)
			return (roots[0]);
		roots[1] = ((-coef[1] + sqrt(disc)) / (2 * coef[0])) - 0.000001;
		return (roots[1] > 0) ? (roots[1]) : -1;
	}
	return (-1);
}

t_cone *create_cone(t_3dpt org, t_3dpt dir, double tilt, t_color col)
{
	t_cone *tmp;

	tmp = (t_cone *)malloc(sizeof(t_cone));

	tmp->vec = create_vec(org, dir);
	tmp->tilt = tilt;
	tmp->col = col;
	tmp->find_insct = find_intersection_cone;
	return (tmp);
}

t_3dpt cone_get_normal_at(t_cone *cone, t_3dpt pt)
{
	t_3dpt norm;

	norm = sub(pt, cone->vec->comp[0]);
	norm = normal(
		sub(norm, multi(cone->vec->comp[1], dot(cone->vec->comp[1], norm))));
	return (norm);
}
