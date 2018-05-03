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
	int			running;
	t_scene		scene;

	if (argc != 2)
		iserr("Usage: ./rtv1 scene");
	running = 1;
	SDL_Init(SDL_INIT_EVERYTHING);
	open_window(&scene);
	read_scene(&scene, argv[1]);
	ft_memset(scene.screen->pixels, 0, scene.screen->h * scene.screen->pitch);
	draw(scene.screen, scene);
	SDL_UpdateWindowSurface(scene.win);
	while (running)
		while (SDL_PollEvent(&scene.event))
		{
			if ((SDL_QUIT == scene.event.type) ||\
					(SDL_KEYDOWN == scene.event.type &&\
					SDL_SCANCODE_ESCAPE == scene.event.key.keysym.scancode))
				running = 0;
		}
	SDL_FreeSurface(scene.screen);
	SDL_DestroyWindow(scene.win);
	SDL_Quit();
	system("leaks rtv1");
	return (0);
}
