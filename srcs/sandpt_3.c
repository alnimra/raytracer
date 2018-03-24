/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandpt_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:06:06 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 18:06:06 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3dpt *add(t_3dpt *pt1, t_3dpt *pt2)
{
    v4sd addition;

    addition = pt1->coord + pt2->coord;
    return (create_3dpt(addition[0], addition[1], addition[2]));
}

t_3dpt *sub(t_3dpt *pt1, t_3dpt *pt2)
{
    v4sd subtraction;

    subtraction = pt1->coord - pt2->coord;
    return (create_3dpt(subtraction[0], subtraction[1], subtraction[2]));
}

double squ(t_3dpt *pt)
{
	return (dot(pt, pt));
}
