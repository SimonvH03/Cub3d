/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/08/28 21:51:28 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH 2560
# define HEIGHT 1440

// scene defaults
# define TILE_SIZE 100
# define C_CEILING 0x000000FF
# define C_FLOOR 0x444444FF
# define C_WALL 0x882222FF

// camera defaults
# define MOVEMENT_SPEED 0.07
# define ROTATION_SPEED 0.03
# define CAMERA_PLANE 0.9

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

typedef struct s_precalc
{
	float			a_sin;
	float			a_cos;
	int				sign_alpha;
}	t_precalc;

typedef struct s_ray
{
	float			dir_y;
	float			dir_x;
	float			step_y;
	float			step_x;
	float			total_y;
	float			total_x;
	short			sign_y;
	short			sign_x;
	int				pos_y;
	int				pos_x;
}	t_ray;

typedef struct s_camera
{
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	t_precalc		precalc;
	float			rotation_speed;
	float			movement_speed;
}	t_camera;

// free: scene->map
typedef struct s_scene
{
	mlx_image_t		*walls;
	mlx_image_t		*background;
	t_camera		camera;
	char			*name;
	int				fd;
	int				**map;
	int				y_max;
	int				x_max;
	mlx_texture_t	north_texture;
	mlx_texture_t	east_texture;
	mlx_texture_t	south_texture;
	mlx_texture_t	west_texture;
	uint32_t		floor;
	uint32_t		ceiling;
	bool			recast;
}	t_scene;

typedef struct s_window
{
	mlx_t			*mlx;
	t_scene			scene;
	bool			redraw;
}	t_window;

typedef void	(mlx_hook)(void *param);
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_scroll)(float, float, void *);

#endif