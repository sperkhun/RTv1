/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:02:09 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:02:11 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	draw_pixel(SDL_Surface *screen, int x, int y, t_vector col)
{
	unsigned char	*pix;
	int				a;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	pix = (unsigned char*)screen->pixels;
	a = x * 4 + y * screen->pitch;
	pix[a++] = col[2] > 255 ? 255 : (int)col[2];
	pix[a++] = col[1] > 255 ? 255 : (int)col[1];
	pix[a++] = col[0] > 255 ? 255 : (int)col[0];
}

static void	rotation(t_vector *v, t_vector rot)
{
	double t;

	if (rot[0] != 0)
	{
		t = (*v)[1];
		(*v)[1] = t * cos(rot[0]) + (*v)[2] * sin(rot[0]);
		(*v)[2] = -t * sin(rot[0]) + (*v)[2] * cos(rot[0]);
	}
	if (rot[1] != 0)
	{
		t = (*v)[0];
		(*v)[0] = t * cos(rot[1]) + (*v)[2] * sin(rot[1]);
		(*v)[2] = -t * sin(rot[1]) + (*v)[2] * cos(rot[1]);
	}
	if (rot[2] != 0)
	{
		t = (*v)[0];
		(*v)[0] = t * cos(rot[2]) - (*v)[1] * sin(rot[2]);
		(*v)[1] = t * sin(rot[2]) + (*v)[1] * cos(rot[2]);
	}
}

void		draw(SDL_Surface *screen, t_scene scene)
{
	int			x;
	int			y;
	t_vector	color;

	y = -(WIN_H / 2);
	while (y < WIN_H / 2)
	{
		x = -(WIN_W / 2);
		while (x < WIN_W / 2)
		{
			scene.camera.vv = (t_vector){x * WIN_W / (1000.0 * WIN_W), y *\
				WIN_H / (1000.0 * WIN_H), 1.0};
			rotation(&scene.camera.vv, scene.camera.rot);
			scene.camera.vv = DIV(scene.camera.vv, LENGTH(scene.camera.vv));
			color = traceray(scene);
			draw_pixel(screen, x + WIN_W / 2, WIN_H / 2 - y, color);
			x++;
		}
		y++;
	}
}
