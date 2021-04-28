/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:00:25 by eblastoi          #+#    #+#             */
/*   Updated: 2021/03/27 17:00:35 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    check_wall(int key, t_all *all)
{
    double  new_x;
    double  new_y;

    new_y = all->plr->y;
    new_x = all->plr->x;
    if (key == W || key == UP)
    {
        new_y += 0.3 * sin(all->plr->direction);
        new_x += 0.3 * cos(all->plr->direction);
    }
    if (key == S || key == DOWN)
    {
        new_y -= 0.3 * sin(all->plr->direction);
        new_x -= 0.3 * cos(all->plr->direction);
    }
    if (key == L)
        all->plr->direction -= 0.1;
    if (key == R)
        all->plr->direction += 0.1;
    if (key == A)
    {
        new_x += 0.3 * sin(all->plr->direction + 2 * M_PI);
        new_y -= 0.3 * cos(all->plr->direction + 2 * M_PI);
    }
    if (key == D)
    {
        new_x += 0.3 * sin(all->plr->direction + M_PI);
        new_y -= 0.3 * cos(all->plr->direction + M_PI);
    }
    if ((new_x < all->params->map_width) && (new_y < all->params->map_height))
    {
        if (all->params->map[(int)new_y][(int)new_x] != '1')
        {
            all->plr->x = new_x;
            all->plr->y = new_y;
            return (0);
        }
    }
    return (1);
}

int     exit_cub(t_all *all)
{
    //free malloc, close fd
    close (all->params->fd);
    free (all->params->map);
    exit(0);
}

int    key_press(int key, t_all *all)
{
    if (key == ESC)
    {
        //free malloc, close fd
        exit_cub(all);
    }
    if ((check_wall(key, all)) == 0)
    {
        // draw_player(all);
        // ft_cast_ray(all);
        // draw_floor_and_ceiling(all);
        cast_rays(all);
        draw_map(all);
        ft_cast_rays(all);
        draw_sprites(all);
        mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    }
    return (0);
}

void error_close(t_all *all)
{
    if (all->params->error == 1)
        printf("Error\nInvalid file name\n");
    else if (all->params->error == 2)
         printf("Error\nInvalid parameter");
    else if (all->params->error == 3)
        printf("Error\nIncorrect number of parameters");
    else if (all->params->error == 4)
        printf("Error\nThere must be one player on the map");
    else if (all->params->error == 5)
       printf("Error\nNot valid map\n");
    else if (all->params->error == 6)
        printf("Error\nResolution must have two positive int value");
    else if (all->params->error == 7)
        printf("Error\nColors must have three int value");
    else if (all->params->error == 8)
        printf("Error\nColors must be in range [0,255]");
    else if (all->params->error == 9)
        printf("Error\nMemory error");
    else if (all->params->error == 10)
        printf("Error\nTexture path error");
    else
        printf("Error\n");
    // free all malloc
    close (all->params->fd);
    free (all->params->map);
    exit (1);
}

void     check_arg_name(char *argv1, t_all *all)
{
    char    *str;
    char    **name;

    str = "cub";
    name = ft_split(argv1, '.');
    if ((ft_strcmp(name[1], str) != 0))
    {
        all->params->error = 1;
        error_close(all);
    }
}

void    start_cub(t_all *all)
{
    init_player(all);
    sprites_init(all);
    all->data->mlx = mlx_init();
    all->data->win = mlx_new_window(all->data->mlx, all->params->width, all->params->height, "cub3D");
    all->data->img = mlx_new_image(all->data->mlx, all->params->width, all->params->height);
    all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, &all->data->line_length, &all->data->endian);
    buff_textures(all);
    // draw_player(&all);
    // ft_cast_ray(&all);
    cast_rays(all);
    draw_map(all);
    ft_cast_rays(all);
    draw_sprites(all);
    mlx_put_image_to_window(all->data->mlx, all->data->win, all->data->img, 0, 0);
    // mlx_put_image_to_window(data.mlx, data.win, all.text[1].texture_img, 0, 0);
    mlx_hook(all->data->win, 2, 1L<<0, key_press, all);
    mlx_hook(all->data->win, 17, 1L<<0, exit_cub, all);
    // mlx_loop_hook(data.mlx, key_press, &all);
    mlx_loop(all->data->mlx);
}

int     main(int argc, char **argv)
{
    t_params    params;
    t_data      data;
    t_player    plr;
    t_all       all;

    all.plr = &plr;
    all.data = &data;
    all.params = &params;
    if (argc == 2)
    {
        check_arg_name(argv[1], &all);
        read_map(argv[1], &all);
        start_cub(&all);
    }
    else if (argc == 3)
    {
        if ((ft_strcmp(argv[2], "--save") == 0))
        {
            check_arg_name(argv[1], &all);
            read_map(argv[1], &all);
            init_player(&all);
            sprites_init(&all);
            data.mlx = mlx_init();
            data.img = mlx_new_image(data.mlx, params.width, params.height);
            data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
            buff_textures(&all);
            cast_rays(&all);
            draw_map(&all);
            ft_cast_rays(&all);
            draw_sprites(&all);
            create_bmp(&all);
        }
        else
        {
            printf("Invalid argument\n");
            exit_cub(&all);
        }

    }
    else if (argc < 2)
        printf("Need a map");
    return (0);
}