/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:10:40 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:10:41 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vector	coefficients(t_object *obj, t_vector d, t_vector oc)
{
	t_vector k;

	if (!ft_strcmp(obj->type, "SPHERE"))
	{
		k[0] = SCALAR(d, d);
		k[1] = 2 * SCALAR(oc, d);
		k[2] = SCALAR(oc, oc) - obj->r * obj->r;
	}
	if (!ft_strcmp(obj->type, "CYLINDER"))
	{
		k[0] = SCALAR(d, d) - pow(SCALAR(d, obj->rot), 2);
		k[1] = 2 * (SCALAR(oc, d) - (SCALAR(d, obj->rot) * SCALAR(oc, obj->rot)));
		k[2] = SCALAR(oc, oc) - pow(SCALAR(oc, obj->rot), 2) - obj->r * obj->r;
	}
	if (!ft_strcmp(obj->type, "CONE"))
	{
		k[0] = SCALAR(d, d) - (pow(SCALAR(d, obj->rot), 2) *\
				(1 + pow(obj->r, 2)));
		k[1] = 2 * (SCALAR(oc, d) - (SCALAR(d, obj->rot) *\
				SCALAR(oc, obj->rot) * (1 + pow(obj->r, 2))));
		k[2] = SCALAR(oc, oc) - (pow(SCALAR(oc, obj->rot), 2) *\
				(1 + pow(obj->r, 2)));
	}
	return (k);
}

static void		object_intersec(t_vector o, t_vector d, t_object *object)
{
	double		disc;
	t_vector	oc;
	t_vector	k;

	oc = o - object->v;
	k = coefficients(object, d, oc);
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
	{
		object->t1 = 10000;
		object->t2 = 10000;
	}
	object->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
	object->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

int				intersection(t_scene *scene, t_vector o, t_vector v, double t_min, double t_max)
{
	int		a;
	int		i;
	double	t[2];

	scene->cl_t = t_max;
	a = -1;
	i = 0;
	while (i < scene->o)
	{
		object_intersec(o, v, &scene->object[i]);
		t[0] = scene->object[i].t1;
		t[1] = scene->object[i].t2;
		if (t[0] >= t_min && t[0] <= t_max && t[0] <= scene->cl_t)
		{
			scene->cl_t = t[0];
			a = i;
		}
		if (t[1] >= t_min && t[1] <= t_max && t[1] <= scene->cl_t)
		{
			scene->cl_t = t[1];
			a = i;
		}
		i++;
	}
	return (a);
}
