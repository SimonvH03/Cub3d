/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:05:56 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/09/16 16:35:21 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void
	scene_recast(
		t_window *window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_R)
		|| mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_W)
		|| mlx_is_key_down(window->mlx, MLX_KEY_A)
		|| mlx_is_key_down(window->mlx, MLX_KEY_S)
		|| mlx_is_key_down(window->mlx, MLX_KEY_D))
		window->scene.recast = true;
}

void
	game_inputs(
		t_window	*window)
{
	wasd_move(window, &window->scene.camera);
	arrowkey_turn(window, &window->scene.camera);
	scene_recast(window);
}

void
	menu_inputs(
		t_window	*window)
{
}

void
	keyhook(
		mlx_key_data_t keydata,
		void *param)
{
	t_window	*window;

	window = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(window->mlx);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS
		&& window->view == GAME)
	{
		toggle_maps(&window->minimap, &window->map);
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		toggle_view(window);
	}
}