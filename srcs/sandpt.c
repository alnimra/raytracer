/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandpt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:30:50 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 11:30:50 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3dpt create_3dpt(double x, double y, double z)
{
	return ((t_3dpt){x, y, z});
}

void set3dpt(t_3dpt *pt, double x, double y, double z)
{
	(*pt)[0] = x;
	(*pt)[1] = y;
	(*pt)[2] = z;
}

double mag(t_3dpt pt)
{
	t_3dpt squares;
	squares = pt * pt;
	return (sqrt(squares[0] + squares[1] + squares[2]));
}

t_3dpt normal(t_3dpt pt)
{
	double m;
	t_3dpt normals;
	t_3dpt mags;

	m = mag(pt);
	mags = create_3dpt(m, m, m);
	normals = pt / mags;
	return (normals);
}


t_3dpt multi(t_3dpt pt, double scalar)
{
    t_3dpt scaled;
    t_3dpt scalars;

	scalars = create_3dpt(scalar, scalar, scalar);
    scaled = pt * scalars;
    return (scaled);
}
