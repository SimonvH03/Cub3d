/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/28 21:44:59 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void
	camera_init(
		t_camera *camera,
		int pos_y,
		int pos_x,
		char direction)
{
	camera->rotation_speed = ROTATION_SPEED;
	camera->movement_speed = MOVEMENT_SPEED;
	camera->pos_y = pos_y + 0.5;
	camera->pos_x = pos_x + 0.5;
	if (direction == 'N')
		camera->dir_y = -1,
		camera->dir_x = 0;
	if (direction == 'E')
		camera->dir_y = 0,
		camera->dir_x = 1;
	if (direction == 'S')
		camera->dir_y = 1,
		camera->dir_x = 0;
	if (direction == 'W')
		camera->dir_y = 0,
		camera->dir_x = -1;
	camera->plane_x = CAMERA_PLANE * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * -camera->dir_x; // maybe change this
	camera->precalc = (t_precalc){sin(ROTATION_SPEED), cos(ROTATION_SPEED), 0};
	// print_camera(camera);
}

static short
	window_init(
		t_window *window)
{
	window->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (window->mlx == NULL)
		return (EXIT_FAILURE);
	window->redraw = true;
	return (EXIT_SUCCESS);
}

short
	scene_init(
		t_scene *scene,
		char *argv_scene)
{
	scene->name = argv_scene;
	scene->ceiling = C_CEILING;// obviously, read these from the scene.cub instead
	scene->floor = C_FLOOR;
	if (map_read(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->recast = true;
	// print_map(scene);
	return (EXIT_SUCCESS);
}

short
	init(
		t_window *window,
		char *argv_scene)
{
	if (window_init(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (scene_init(&window->scene, argv_scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_images(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}