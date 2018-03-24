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

double dot(t_3dpt pt1, t_3dpt pt2)
{
    t_3dpt product;

    product = pt1 * pt2;
    return (product[0] + product[1] + product[2]);
}

t_3dpt cross(t_3dpt pt1, t_3dpt pt2)
{
    t_3dpt top;
    t_3dpt bot;
    t_3dpt res;

	top = create_3dpt(pt1[1] * pt2[2], pt1[2] * pt2[0], pt1[0] * pt2[1]);
	bot = create_3dpt(pt1[2] * pt2[1], pt1[0] * pt2[2], pt1[1] * pt2[0]);
    res = top - bot;
    return (res);
}

t_3dpt add(t_3dpt pt1, t_3dpt pt2)
{
    t_3dpt addition;

    addition = pt1 + pt2;
    return (addition);
}

t_3dpt sub(t_3dpt pt1, t_3dpt pt2)
{
    t_3dpt subtraction;

    subtraction = pt1 - pt2;
    return (subtraction);
}

double squ(t_3dpt pt)
{
	return (dot(pt, pt));
}
