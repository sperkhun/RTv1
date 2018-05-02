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

double	lighting(t_vector p, t_vector n, t_scene scene, t_object object)
{
	t_vector	l;
	double		i;
	double		v;
	int			a;

	i = 0.0;
	a = -1;
	while (++a < scene.l)
	{
		l = scene.light[a].v - p;
		v = (n * l)[0] + (n * l)[1] + (n * l)[2];
		scene.t_min = 0.001;
		scene.t_max = 1;
		if (scene.shadows && intersection(&scene, p, l) >= 0)
			continue ;
		v > 0 ? i += scene.light[a].intensity * v / (LENGTH(n) * LENGTH(l)) : 0;
		if (object.specular != -1)
		{
			l = MULT(n, 2 * SCALAR(n, l)) - l;
			v = SCALAR(l, -scene.camera.vv);
			v > 0 ? i += scene.light[a].intensity * pow(v / (LENGTH(l) *\
				LENGTH(-scene.camera.vv)), object.specular) : 0;
		}
	}
	return (i);
}
