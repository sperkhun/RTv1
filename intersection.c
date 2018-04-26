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

static void	sphere(t_vector o, t_vector d, t_object *object)
{
	double disc;
	t_vector oc;
	t_vector k;

	oc = o - object->v;
	k[0] = SCALAR(d, d);
	k[1] = 2 * SCALAR(oc, d);
	k[2] = SCALAR(oc, oc) - object->r * object->r;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
	{
		object->t1 = 10000;
		object->t2 = 10000;
	}
	object->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
	object->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

static void	cylinder(t_vector o, t_vector d, t_object *object)
{
	double disc;
	t_vector oc;
	t_vector k;
	t_vector v;

	v = (t_vector){0, 1, 0};
	oc = o - object->v;
	k[0] = SCALAR(d, d) - pow(SCALAR(d, v), 2);
	k[1] = 2 * (SCALAR(oc, d) - SCALAR(d, v) * SCALAR(oc, v));
	k[2] = SCALAR(oc, oc) - pow(SCALAR(oc, v), 2) - object->r * object->r;
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
	{
		object->t1 = 10000;
		object->t2 = 10000;
	}
	object->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
	object->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

static void	cone(t_vector o, t_vector d, t_object *object)
{
	double disc;
	t_vector oc;
	t_vector k;
	t_vector v;

	v = (t_vector){0, 1, 0};
	oc = o - object->v;
	k[0] = SCALAR(d, d) - pow(SCALAR(d, v), 2) * (1 + pow(object->k, 2));
	k[1] = 2 * (SCALAR(oc, d) - SCALAR(d, v) * SCALAR(oc, v) * (1 + pow(object->k, 2)));
	k[2] = SCALAR(oc, oc) - pow(SCALAR(oc, v), 2) * (1 + pow(object->k, 2));
	disc = k[1] * k[1] - 4 * k[0] * k[2];
	if (disc < 0)
	{
		object->t1 = 10000;
		object->t2 = 10000;
	}
	object->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
	object->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

int intersection(t_object *object, t_vector o, t_vector v, double t_min, double t_max, double *cl_t)
{
	int a;
	int i;
	double t[2];

	*cl_t = t_max;
	a = -1;
	i = 0;
	while (i < 4)
	{
		!ft_strcmp(object[i].type, "SPHERE") ? sphere(o, v, &object[i]) : 0;
		!ft_strcmp(object[i].type, "CYLINDER") ? cylinder(o, v, &object[i]) : 0;
		!ft_strcmp(object[i].type, "CONE") ? cone(o, v, &object[i]) : 0;
		t[0] = object[i].t1;
		t[1] = object[i].t2;
		if (t[0] >= t_min && t[0] <= t_max && t[0] <= *cl_t)
		{
			*cl_t = t[0];
			a = i;
		}
		if (t[1] >= t_min && t[1] <= t_max && t[1] <= *cl_t)
		{
			*cl_t = t[1];
			a = i;
		}
		i++;
	}
	return (a);
}