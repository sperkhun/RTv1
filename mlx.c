/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:52:41 by sperkhun          #+#    #+#             */
/*   Updated: 2018/05/03 14:52:42 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	open_window(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIN_W, WIN_H, "WOLF3D");
	if (!scene->mlx || !scene->win)
		iserr("Error", 0);
	if (!(scene->img = mlx_new_image(scene->mlx, WIN_W, WIN_H)))
	{
		perror("Error");
		exit(1);
	}
	scene->pxl_img = mlx_get_data_addr(scene->img, &(scene->bpp),\
										&(scene->s_line), &(scene->ed));
}

int		key_hook(int key, t_scene *scene)
{
	if (key == 53)
	{
		mlx_destroy_image(scene->mlx, scene->img);
		mlx_destroy_window(scene->mlx, scene->win);
		system("leaks RTv1");
		exit(0);
	}
	return (0);
}

int		exit_x(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	system("leaks RTv1");
	exit(0);
	return (0);
}
