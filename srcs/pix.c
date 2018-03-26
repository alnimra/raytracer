/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:11:41 by mray              #+#    #+#             */
/*   Updated: 2018/03/24 15:11:41 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	store_pix(t_canvas *canvas, int x, int y, unsigned int c)
{
	int i;

	i = (x * 4) + (y * canvas->size_line);
	*(canvas->pix_data + i) = c;
	*(canvas->pix_data + i + 1) = c >> 8;
	*(canvas->pix_data + i + 2) = c >> 16;
}

void	store_color_pix(t_canvas *canvas, int x, int y, t_color color)
{
	int i;

	i = (x * 4) + (y * canvas->size_line);
	*(canvas->pix_data + i) = color[0] * 255;
	*(canvas->pix_data + i + 1) = color[1] * 255;
	*(canvas->pix_data + i + 2) = color[2] * 255;
}
