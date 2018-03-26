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

t_color	create_color(double r, double g, double b, double special)
{
	return ((t_color){r, g, b, special});
}

t_color	col_multi(t_color color, double scalar)
{
	return (create_color(color[0] * scalar, color[1] * scalar,
						color[2] * scalar, color[3]));
}

t_color	add_col(t_color color1, t_color color2)
{
	return (create_color(color1[0] + color2[0], color1[1] + color2[1],
						color1[2] + color2[2], color1[0]));
}

t_color	multi_col(t_color color1, t_color color2)
{
	return (create_color(color1[0] * color2[0], color1[1] * color2[1],
						color1[2] * color2[2], color1[0]));
}

t_color	avg_col(t_color color1, t_color color2)
{
	return (create_color((color1[0] + color2[0]) / 2,
						(color1[1] + color2[1]) / 2,
						(color1[2] + color2[2]) / 2, color1[0]));
}
