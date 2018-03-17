/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandpt_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:39:52 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 16:39:52 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double mag(t_3dpt *pt)
{
    v4sd squares;
    squares = pt->coord * pt->coord;
    return (sqrt(squares[0] + squares[1] + squares[2]));
}

t_3dpt *normal(t_3dpt *pt)
{
    double m;
    v4sd normals;
    v4sd mags;
    
    m = mag(pt);
    mags[0] = m;
    mags[1] = m;
    mags[2] = m;
    normals = pt->coord / mags;
    return (create_3dpt(normals[0], normals[1], normals[2]));
}

t_3dpt *multi(t_3dpt *pt, double scalar)
{
    v4sd scaled;
    v4sd scalars;

    scalars[0] = scalar;
    scalars[1] = scalar;
    scalars[2] = scalar;
    scaled = pt->coord * scalars;
    return (create_3dpt(scaled[0], scaled[1], scaled[2]));
}

double dot(t_3dpt *pt1, t_3dpt *pt2)
{
    v4sd product;

    product = pt1->coord * pt2->coord;
    return (product[0] + product[1] + product[2]);
}

t_3dpt *cross(t_3dpt *pt1, t_3dpt *pt2)
{
    v4sd top;
    v4sd bot;
    v4sd res;

    top[0] = pt1->coord[1] * pt2->coord[2];
    top[1] = pt1->coord[2] * pt2->coord[0];
    top[2] = pt1->coord[0] * pt2->coord[1];
    bot[0] = pt1->coord[2] * pt2->coord[1];
    bot[1] = pt1->coord[0] * pt2->coord[2];
    bot[2] = pt1->coord[1] * pt2->coord[0];
    res = top - bot;
    return (create_3dpt(res[0], res[1], res[2]));
}