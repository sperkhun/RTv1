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
	pix[a++] = col[2] > 255 ? 255 : col[2];
	pix[a++] = col[1] > 255 ? 255 : col[1];
	pix[a++] = col[0] > 255 ? 255 : col[0];
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
			scene.camera.vv = (t_vector){x * scene.camera.d / WIN_W, y *\
				0.8 / WIN_H, 1.0};
			scene.camera.vv += scene.camera.rot;
			scene.camera.vv = DIV(scene.camera.vv, LENGTH(scene.camera.vv));
			color = traceray(scene);
			draw_pixel(screen, x + WIN_W / 2, WIN_H / 2 - y, color);
			x++;
		}
		y++;
	}
}
