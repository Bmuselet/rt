/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:38:03 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/28 20:01:28 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw(t_env *e)
{
	e->img = new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->cam.forward = vector_int_product(e->cam.dir, -1);
	e->cam.left = vector_cross(
		vector_normalize((t_vec){0.0, 1.0, 0.0}), e->cam.dir);
	e->cam.up = vector_cross(e->cam.forward, e->cam.left);
	multi_thread(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		get_objs_and_cam(&e, av[1]);
		e.mlx = mlx_init();
		e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "RT beta 0.2");
		e.cam.antialiasing = OFF;
		e.cam.cel_shading = OFF;
		draw(&e);
		mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
		mlx_hook(e.win, EXIT_PRESS, EXIT_PRESS_MASK, &button_exit, &e);
		mlx_loop(e.mlx);
	}
	/*else
		error(INVALID_ARG);*/
}
