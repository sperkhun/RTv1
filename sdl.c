/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
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
	if (!(scene->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,\
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI)))
		iserr("Error", 0);
	scene->screen = SDL_GetWindowSurface(scene->win);
}
