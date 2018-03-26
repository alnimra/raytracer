/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:11:01 by mray              #+#    #+#             */
/*   Updated: 2018/03/25 17:11:01 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	bness(t_color color)
{
	return ((color[0] + color[1] + color[2]) / 3);
}

void	correct_color_leaks(t_color *color)
{
	double all_light;
	double exc_light;

	all_light = (*color)[0] + (*color)[1] + (*color)[2];
	exc_light = all_light - 3;
	if (exc_light > 0)
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
