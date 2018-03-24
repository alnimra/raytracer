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
		mlx_loop(gl->lib);
	}
}
