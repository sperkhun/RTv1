/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:05:19 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:05:20 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	lighting(t_vector p, t_vector n, t_scene scene, t_object object)
{
	t_vector	l;
	double		i;
	double		vv;
	t_vector	v;
	t_vector	h;
	int			a;

	i = 0.0;
	a = -1;
	while (++a < scene.l)
	{
		l = scene.light[a].v - p;
		vv = SCALAR(n, l);
		scene.t_min = 0.001;
		scene.t_max = 1;
		if (scene.shadows && intersection(&scene, p, l) >= 0)
			continue ;
		vv > 0 ? i += scene.light[a].intensity * vv / (LENGTH(n) * LENGTH(l)) : 0;
		// if (object.specular != -1)
		// {
		// 	l = MULT(n, 2 * SCALAR(n, l)) - l;
		// 	v = SCALAR(l, -scene.camera.vv);
		// 	v > 0 ? i += scene.light[a].intensity * pow(v / (LENGTH(l) *\
		// 		LENGTH(-scene.camera.vv)), object.specular) : 0;
		// }
		l = NORM((scene.light[a].v - p));
		v = NORM((scene.camera.ov - p));
		h = NORM((MULT(n, (SCALAR(n, v) * 2)) - v));
		// object.col = MULT(object.col, (fmax(SCALAR(n, l), 0.0)));
		
		if (object.specular >= 10)
		{
			object.col = object.col + MULT(((t_vector){150, 150, 150}), (scene.light[a].intensity * pow(fmax(SCALAR(l, h), 0.0) ,object.specular)));
		}
	}
	object.col = MULT(object.col, i);
	return (object.col);
}
