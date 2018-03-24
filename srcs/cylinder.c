/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:01:00 by mray              #+#    #+#             */
/*   Updated: 2018/03/22 16:01:00 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double find_intersection_cyl(t_cyl *cyl, t_vec *vec)
{
	double a;
	double b;
	double c;
	double discriminant;
	double roots[2];

	a = squ(sub(vec->comp[1], multi(cyl->vec->comp[1],
									dot(vec->comp[1], cyl->vec->comp[1]))));
	b = 2 * dot(sub(vec->comp[1], multi(cyl->vec->comp[1],
										dot(vec->comp[1], cyl->vec->comp[1]))),
				sub(sub(vec->comp[0], cyl->vec->comp[0]),
					multi(cyl->vec->comp[1],
						  dot(sub(vec->comp[0], cyl->vec->comp[0]),
							  cyl->vec->comp[1]))));
	c = squ(sub(
			sub(vec->comp[0], cyl->vec->comp[0]),
			multi(cyl->vec->comp[1], dot(sub(vec->comp[0], cyl->vec->comp[0]),
										 cyl->vec->comp[1])))) -
		(cyl->rad * cyl->rad);
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		roots[0] = ((-b - sqrt(discriminant)) / (2 * a)) - 0.000001;
		if (roots[0] > 0)
			return (roots[0]);
		roots[1] = ((-b + sqrt(discriminant)) / (2 * a)) - 0.000001;
		return (roots[1] > 0) ? (roots[1]) : -1;
	}
	return (-1);
}

t_cyl *create_cyl(t_3dpt org, t_3dpt dir, double rad, t_color col)
{
	t_cyl *tmp;

	tmp = (t_cyl *)malloc(sizeof(t_cyl));

	tmp->vec = create_vec(org, dir);
	tmp->rad = rad;
	tmp->col = col;
	tmp->find_insct = find_intersection_cyl;
	return (tmp);
}

t_3dpt cyl_get_normal_at(t_cyl *cyl, t_3dpt pt)
{
	t_3dpt norm;

	norm = sub(pt, cyl->vec->comp[0]);
	norm =
		normal(sub(norm, multi(cyl->vec->comp[1], dot(cyl->vec->comp[1], norm))));
	return (norm);
}
