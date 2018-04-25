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
    pix[a++] = col[2] > 255 ? 255 : col[2];
    pix[a++] = col[1] > 255 ? 255 : col[1];
    pix[a++] = col[0] > 255 ? 255 : col[0];
}

double      lighting(t_vector p, t_vector n, t_vector v, t_light *light, t_sphere sphere)
{
    t_vector l;
    t_vector r;
    double     i;
    double     n_l;
    double     r_v;
    int a;

    i = 0.0;
    a = 0;
    while (a < 1)
    {
        l = light[a].v - p;
        n_l = (n * l)[0] + (n * l)[1] + (n * l)[2];
        if (n_l > 0)
            i += light[a].intensity * n_l / (LENGTH(n) * LENGTH(l));
        if (sphere.specular != -1)
        {
            r = MULT(n, 2 * SCALAR(n, l)) - l;
            r_v = SCALAR(r, v);
            if (r_v > 0)
            {
                i += light[a].intensity * pow(r_v / (LENGTH(r) * LENGTH(v)), sphere.specular);
            }
        }
        a++;
    }
    return (i);
}

void cl_inter(t_camera camera, t_sphere *sphere)
{
    double disc;
    t_vector oc;
    t_vector k;

    oc = camera.ov - sphere->v;
    k[0] = SCALAR(camera.vv, camera.vv);
    k[1] = 2 * SCALAR(oc, camera.vv);
    k[2] = SCALAR(oc, oc) - sphere->r * sphere->r;
    disc = k[1] * k[1] - 4 * k[0] * k[2];
    if (disc < 0)
    {
        sphere->t1 = 10000;
        sphere->t2 = 10000;
    }
    sphere->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
    sphere->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

// void cl_inter_c(t_camera camera, t_sphere *sphere)
// {
//     double disc;
//     t_vector oc;
//     t_vector k;

//     oc = camera.ov - sphere->v;
//     k[0] = SCALAR(camera.vv, camera.vv) - pow(SCALAR(camera.vv, sphere->vv), 2);
//     k[1] = 2 * (SCALAR(oc, camera.vv) - SCALAR(camera.vv, sphere->vv) * SCALAR(oc, sphere->vv));
//     k[2] = SCALAR(oc, oc) - pow(SCALAR(oc, sphere->vv), 2) - sphere->r * sphere->r;
//     disc = k[1] * k[1] - 4 * k[0] * k[2];
//     if (disc < 0)
//     {
//         sphere->t1 = 10000;
//         sphere->t2 = 10000;
//     }
//     sphere->t1 = (-k[1] + sqrt(disc)) / (2 * k[0]);
//     sphere->t2 = (-k[1] - sqrt(disc)) / (2 * k[0]);
// }

int intersection(t_objects objects, double t_min, double t_max, double *cl_t)
{
    int a;
    int i;
    double t[2];

    *cl_t = t_max;
    a = -1;
    i = 0;
    while (i < 2)
    {
        cl_inter(objects.camera, &objects.sphere[i]);
        t[0] = objects.sphere[i].t1;
        t[1] = objects.sphere[i].t2;
        if (t[0] >= t_min && t[0] < 10000 && t[0] < *cl_t)
        {
            *cl_t = t[0];
            a = i;
        }
        if (t[1] >= t_min && t[1] < 10000 && t[1] < *cl_t)
        {
            *cl_t = t[1];
            a = i;
        }
        i++;
    }
    return (a);
}

t_vector traceray(t_objects objects)
{
    t_vector    p;
    t_vector    n;
    t_vector    color;
    double      i;
    int         a;
    // double m;

    a = intersection(objects, 1, 10000, &objects.cl_t);
    if (a < 0)
        return ((t_vector){0, 0, 0});
    p = objects.camera.ov + MULT(objects.camera.vv, objects.cl_t);
    //m = SCALAR(objects.camera.vv, objects.sphere[a].vv) * objects.cl_t + SCALAR(objects.camera.ov - objects.sphere[a].v, objects.sphere[a].vv);
    n = p - objects.sphere[a].v;
    //n = p - objects.sphere[a].v - MULT(objects.sphere[a].vv, m);
    n = DIV(n, LENGTH(n));
    i = lighting(p, n, -objects.camera.vv, objects.light, objects.sphere[a]);
    color = MULT(objects.sphere[a].col, i);
    return (color);
}

void draw(SDL_Surface *screen, t_objects objects)
{
    int x;
    int y;
    t_vector color;

    y = -(WIN_H / 2);
    while (y < WIN_H / 2)
    {
        x = -(WIN_W / 2);
        while (x < WIN_W / 2)
        {
            objects.camera.vv = (t_vector){x * objects.camera.d / WIN_W, y * 0.8 / WIN_H, 1.0};
            color = traceray(objects);
            draw_pixel(screen, x + WIN_W / 2, WIN_H / 2 - y, color);
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
    t_objects objects;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Hello SDL World",\
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == win)
        exit (1);
    screen = SDL_GetWindowSurface(win);
    // const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    objects.sphere = (t_sphere*)malloc(sizeof(t_sphere) * 2);
    objects.light = (t_light*)malloc(sizeof(t_light) * 2);
    objects.camera.ov = (t_vector){0, 0, 0};
    objects.camera.d = 1;
    objects.light[0].v = (t_vector){4, 2, 0};
    objects.light[0].intensity = 0.9;
    // objects.light[1].v = (t_vector){-10, 1, 2};
    // objects.light[1].intensity = 0.6;
    objects.sphere[0].v = (t_vector){0, -9001, 0};
    objects.sphere[0].r = 9000;
    objects.sphere[0].specular = -1;
    objects.sphere[0].col = (t_vector){0, 255, 0};
    objects.sphere[1].v = (t_vector){0, 0, 5.0};
    objects.sphere[1].r = 1;
    objects.sphere[1].specular = -1;
    objects.sphere[1].col = (t_vector){255, 0, 0};
    SDL_LockSurface(screen);
    ft_memset(screen->pixels, 0, screen->h * screen->pitch);
    draw(screen, objects);
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

