/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_scene_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:58:42 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/28 21:09:04 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static short
	map_size(
		t_scene *scene)
{
	char	*buffer;
	int		temp_x;

	scene->fd = open(scene->name, O_RDONLY);
	scene->y_max = 0;
	scene->x_max = 0;
	buffer = get_next_line(scene->fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	while (buffer)
	{
		temp_x = ft_strlen(buffer);
		if (buffer[temp_x - 1] == '\n')
			--temp_x;
		if (temp_x > scene->x_max)
			scene->x_max = temp_x;
		free(buffer);
		++scene->y_max;
		buffer = get_next_line(scene->fd);
	}
	close(scene->fd);
	return (EXIT_SUCCESS);
}

static short
	map_calloc(
		t_scene *scene)
{
	int	y;

	scene->map = (int **)malloc(sizeof(int *) * scene->y_max + 1);
	if (scene->map == NULL)
		return (EXIT_FAILURE);
	ft_bzero(scene->map, scene->y_max + 1);
	y = 0;
	while (y < scene->y_max)
	{
		scene->map[y] = (int *)malloc(sizeof(int) * scene->x_max);
		if (scene->map[y] == NULL)
			return (EXIT_FAILURE);
		ft_bzero(scene->map[y], scene->x_max);
		++y;
	}
	return (EXIT_SUCCESS);
}

static short
	map_fill_row(
		t_scene *scene,
		int y,
		char *buffer)
{
	int		x;

	x = 0;
	while (buffer[x] && buffer[x] != '\n')
	{
		if (buffer[x] == ' ' || buffer[x] == '0')
			scene->map[y][x] = 0;
		else if (buffer[x] == '1')
			scene->map[y][x] = 1;
		else if (buffer[x] == 'N' || buffer[x] == 'E'
			|| buffer[x] == 'S' || buffer[x] == 'W')
		{
			scene->map[y][x] = 0;
			camera_init(&scene->camera, y, x, buffer[x]);
		}
		else
			return (EXIT_FAILURE);
		++x;
	}
	while (x < scene->x_max)
	{
		scene->map[y][x] = 0;
		++x;
	}
	return (EXIT_SUCCESS);
}

static short
	map_fill(
		t_scene *scene)
{
	char	*buffer;
	int		y;

	scene->fd = open(scene->name, O_RDONLY);
	if (scene->fd == -1)
		return (EXIT_FAILURE);
	y = 0;
	buffer = get_next_line(scene->fd);
	if (buffer == NULL)
		return (EXIT_FAILURE);
	while (buffer && y < scene->y_max)
	{
		if (map_fill_row(scene, y, buffer) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(buffer);
		++y;
		buffer = get_next_line(scene->fd);
	}
	if (buffer)
		free(buffer);
	close(scene->fd);
	return (EXIT_SUCCESS);
}

short
	map_read(
		t_scene *scene)
{
	if (map_size(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_calloc(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (map_fill(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// print_map(scene);
	return (EXIT_SUCCESS);
}