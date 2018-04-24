/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:20:22 by sperkhun          #+#    #+#             */
/*   Updated: 2018/02/28 17:34:27 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void    draw_pixel(SDL_Surface *screen, int x, int y, t_vector col)
{
    unsigned char *pix;
    int a;

    if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
        return ;
    pix = (unsigned char*)screen->pixels;
    a = x * 4 + y * screen->pitch;
    pix[a++] = col[2];
    pix[a++] = col[1];
    pix[a++] = col[0];
}

void    draw_scene(SDL_Surface *screen, t_sphere sphere, t_camera camera, t_light light)
{
    int x;
    int y;
    double cl_t;
    double t1;
    double t2;
    double k1;
    double k2;
    double k3;
    double disc;
    t_vector oc;
    t_vector tmp;
    t_vector p;
    t_vector n;
    t_vector l;
    double     i;

    y = -(WIN_H / 2);
    while (y < WIN_H / 2)
    {
        x = -(WIN_W / 2);
        while (x < WIN_W / 2)
        {
            camera.vv = (t_vector){x * camera.d / WIN_W, y * 0.8 / WIN_H, 1.0};
            cl_t = 10000;
            oc = camera.ov - sphere.v;
            tmp = camera.vv * camera.vv;
            k1 = tmp[0] + tmp[1] + tmp[2];
            tmp = oc * camera.vv;
            k2 = 2 * (tmp[0] + tmp[1] + tmp[2]);
            tmp = oc * oc;
            k3 = (tmp[0] + tmp[1] + tmp[2]) - sphere.r * sphere.r;
            disc = k2 * k2 - 4 * k1 * k3;
            if (disc < 0)
            {
                x++;
                continue ;
            }
            t1 = (-k2 + sqrt(disc)) / (2 * k1);
            t2 = (-k2 - sqrt(disc)) / (2 * k1);
            if (t1 >= 1 && t1 <= 10000 && t1 < cl_t)
                cl_t = t1;
            if (t2 >= 1 && t2 <= 10000 && t2 < cl_t)
                cl_t = t2;
            if (cl_t < 10000)
            {
                i = 0.0;
                p = camera.ov + (t_vector){cl_t, cl_t, cl_t} * camera.vv;
                n = p - sphere.v;
                n = n / (t_vector){sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]), sqrt(n[0] * n[0]\
                    + n[1] * n[1] + n[2] * n[2]), sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2])};
                l = light.v - p;
                t1 = (n * l)[0] + (n * l)[1] + (n * l)[2];
                if (t1 > 0)
                    i = light.intensity * t1 / ((sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2])) *\
                        (sqrt(l[0] * l[0] + l[1] * l[1] + l[2] * l[2])));
                draw_pixel(screen, x + WIN_W / 2, WIN_H / 2 - y, sphere.col * (t_vector){i, i, i});
            }
            x++;
        }
        y++;
    }
}

int main()
{
    int running = 1;
    SDL_Event event;
    SDL_Window *win;
    SDL_Surface *screen;
    t_sphere sphere;
    t_camera camera;
    t_light  light;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Hello SDL World",\
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == win)
        exit (1);
    screen = SDL_GetWindowSurface(win);
    // const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    
    camera.ov = (t_vector){0, 0, 0};
    camera.d = 1;
    light.v = (t_vector){4, 2, 0};
    light.intensity = 0.8;
    SDL_LockSurface(screen);
    ft_memset(screen->pixels, 0, screen->h * screen->pitch);
    sphere.v = (t_vector){0, -5001, 0};
    sphere.r = 5000;
    sphere.col = (t_vector){0, 255, 0};
    draw_scene(screen, sphere, camera, light);
    sphere.v = (t_vector){0, 0, 5.0};
    sphere.r = 1;
    sphere.col = (t_vector){255, 0, 0};
    draw_scene(screen, sphere, camera, light);
    SDL_UnlockSurface(screen);
    SDL_UpdateWindowSurface(win);
    while (running)
        while(SDL_PollEvent(&event))
        {
            if((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
                running = 0;
            // if(event.type == SDL_MOUSEBUTTONDOWN && event.type == SDL_MOUSEMOTION)
            // {
            //     draw_pixel(win, screen, event.button.x, event.button.y);
                // if(event.button.button == SDL_BUTTON_RIGHT)
                //     ARRAY_texturesState[1] = 1;
                // if((event.button.button == SDL_BUTTON_LEFT) && (event.button.x >= src.x) &&\
                //     (event.button.y >= src.y) &&\
                //     (event.button.x <= src.w + src.x) &&\
                //     (event.button.y <= src.h + src.y))
                //     ARRAY_texturesState[1] = 0;
            // }
            
            //ZOOM----------------------------------------------------------------
            /*if(keyboardState[SDL_SCANCODE_KP_PLUS])
            {
                TESTtexture_SCALE += 0.02;
                src.h = back1_HEIGH * TESTtexture_SCALE;
                src.w = back1_WIGHT * TESTtexture_SCALE;
            }
            if(keyboardState[SDL_SCANCODE_KP_MINUS])
            {
                TESTtexture_SCALE -= 0.02;
                src.h = back1_HEIGH * TESTtexture_SCALE;
                src.w = back1_WIGHT * TESTtexture_SCALE;
            }
            render_UPDATE(ren, ARRAY_textures, ARRAY_rect, ARRAY_texturesState);*/
        }
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(win);
    SDL_Quit();
    system("leaks rtv1");
    return (0);
}

