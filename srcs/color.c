/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:22:06 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 19:22:06 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color create_color(double r, double g, double b, double special)
{
    return ((t_color){r, g, b, special});
}

double bness(t_color color)
{
    return ((color[0] + color[1] + color[2]) / 3);
}

t_color col_multi(t_color color, double scalar)
{
    return create_color(color[0] * scalar, color[1] * scalar, color[2] * scalar, color[3]);
}

t_color add_col(t_color color1, t_color color2)
{
    return create_color(color1[0] + color2[0], color1[1] + color2[1], color1[2] + color2[2], color1[0]);
}

t_color multi_col(t_color color1, t_color color2)
{
    return create_color(color1[0] * color2[0], color1[1] * color2[1], color1[2] * color2[2], color1[0]);
}

t_color avg_col(t_color color1, t_color color2)
{
    return create_color((color1[0] + color2[0]) / 2, (color1[1] + color2[1]) / 2, (color1[2] + color2[2]) / 2, color1[0]);
}

void correct_color_leaks(t_color *color)
{
	double all_light;
	double exc_light;

	all_light = (*color)[0] + (*color)[1] + (*color)[2];
	exc_light = all_light - 3;
	if(exc_light > 0)
	{
		(*color)[0] += exc_light * ((*color)[0] / all_light);
		(*color)[1] += exc_light * ((*color)[1] / all_light);
		(*color)[2] += exc_light * ((*color)[2] / all_light);
	}
	(*color)[0] = ((*color)[0] > 1) ? 1 : (*color)[0];
	(*color)[1] = ((*color)[1] > 1) ? 1 : (*color)[1];
	(*color)[2] = ((*color)[2] > 1) ? 1 : (*color)[2];
	(*color)[0] = ((*color)[0] < 0) ? 0 : (*color)[0];
	(*color)[1] = ((*color)[1] < 0) ? 0 : (*color)[1];
	(*color)[2] = ((*color)[2] < 0) ? 0 : (*color)[2];
}
