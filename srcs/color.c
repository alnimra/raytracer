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

t_color *create_color(double r, double g, double b, double special)
{
    t_color *tmp;

    tmp = (t_color *)malloc(sizeof(t_color));
    tmp->prop[0] = r;
    tmp->prop[1] = g;
    tmp->prop[2] = b;
    tmp->prop[3] = special;
    return (tmp);
}

double bness(t_color *color)
{
    return ((color->prop[0] + color->prop[1] + color->prop[2]) / 3);
}

t_color *color_multi(t_color *color, double scalar)
{
    return create_color(color->prop[0] * scalar, color->prop[1] * scalar, color->prop[2] * scalar, color->prop[3]);
}

t_color *add_col(t_color *color1, t_color *color2)
{
    return create_color(color1->prop[0] + color2->prop[0], color1->prop[1] + color2->prop[1], color1->prop[2] + color2->prop[2], color1->prop[0]);
}

t_color *multi_col(t_color *color1, t_color *color2)
{
    return create_color(color1->prop[0] * color2->prop[0], color1->prop[1] * color2->prop[1], color1->prop[2] * color2->prop[2], color1->prop[0]);
}

t_color *avg_col(t_color *color1, t_color *color2)
{
    return create_color((color1->prop[0] + color2->prop[0]) / 2, (color1->prop[1] + color2->prop[1]) / 2, (color1->prop[2] + color2->prop[2]) / 2, color1->prop[0]);
}