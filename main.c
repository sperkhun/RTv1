/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:20:22 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/28 11:39:13 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_scene		scene;

	if (argc != 2)
		iserr("Usage: ./rtv1 scene", 1);
	open_window(&scene);
	read_scene(&scene, argv[1]);
	draw(scene);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_hook(scene.win, 17, 5, exit_x, &scene);
	mlx_hook(scene.win, 2, 5, key_hook, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
