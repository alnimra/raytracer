/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:57:35 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 13:57:35 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int  x = 0;
int  y = 0;
void store_pix(t_canvas *canvas, int x, int y, unsigned int c)
{
	int i;

	i = (x * 4) + (y * canvas->size_line);
	*(canvas->pix_data + i) = c;
	*(canvas->pix_data + i + 1) = c >> 8;
	*(canvas->pix_data + i + 2) = c >> 16;
}

void store_color_pix(t_canvas *canvas, int x, int y, t_color *color)
{
	int i;

	i = (x * 4) + (y * canvas->size_line);
	*(canvas->pix_data + i) = color->prop[0] * 255;
	*(canvas->pix_data + i + 1) = color->prop[1] * 255;
	*(canvas->pix_data + i + 2) = color->prop[2] * 255;
}

int main(int argc, char **argv)
{
	t_gl *	gl;
	void *	mlx;
	void *	window;
	t_canvas *canvas;
	t_params *para;
	t_inputs *inputs;
	if (argc == 2)
	{
		argv[0] = 0;
		para = (t_params *)malloc(sizeof(t_params));
		inputs = (t_inputs *)malloc(sizeof(t_inputs));
		mlx = mlx_init();
		window = mlx_new_window(mlx, WIDTH, HEIGHT, "RayTracer 1.0");
		gl = create_gl(mlx, window);
		canvas = create_canvas(gl);
		para->p1 = gl;
		para->p2 = canvas;
		para->p3 = inputs;
		ft_putstr("hello");
		parse_obj_data(gl, read_in(argv[1]));
		ft_putendl("Entering Scenify");
		scenify(gl, canvas);
		// mlx_hook(gl->surf, 2, 0, key_handler, para);
		// mlx_hook(gl->surf, 4, 0, mouse_handler, para);
		// mlx_hook(gl->surf, 6, 0, hover_handler, para);
		// draw_frac(gl, canvas);ß
		mlx_loop(gl->lib);
	}
}
