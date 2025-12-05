/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:53 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/05 13:30:55 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	main_validate(t_data *data)
{
	char	*err_msg;

	if (!data->map)
	{
		write(1, "Error\nFailed to read map or map not rectangular\n", 49);
		return (0);
	}
	err_msg = NULL;
	if (!validate_map_structure(data, data->map, &err_msg))
	{
		(void)err_msg;
		write(1, "Error\nInvalid map\n", 19);
		free_map(data->map, data->rows);
		return (0);
	}
	if (!flood_check(data))
	{
		write(1, "Error\nMap is not solvable\n", 27);
		free_map(data->map, data->rows);
		return (0);
	}
	return (1);
}

static int	main_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		free_map(data->map, data->rows);
		return (0);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "so_long");
	if (!data->win_ptr)
	{
		free_map(data->map, data->rows);
		return (0);
	}
	return (1);
}

static void	main_load_images(t_data *data)
{
	int	w;
	int	h;

	data->background = mlx_xpm_file_to_image(data->mlx_ptr,
			"./sprites/background.xpm", &w, &h);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./sprites/wall.xpm",
			&w, &h);
	data->floor = mlx_xpm_file_to_image(data->mlx_ptr, "./sprites/floor.xpm",
			&w, &h);
	data->exit_close = mlx_xpm_file_to_image(data->mlx_ptr,
			"./sprites/exit_close.xpm", &w, &h);
	data->treasure = mlx_xpm_file_to_image(data->mlx_ptr,
			"./sprites/treasure.xpm", &w, &h);
	data->exit_open = mlx_xpm_file_to_image(data->mlx_ptr,
			"./sprites/steps.xpm", &w, &h);
	data->player_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./sprites/player.xpm", &data->player_w, &data->player_h);
	if (!data->background || !data->wall || !data->floor || !data->exit_close
		|| !data->treasure || !data->exit_open || !data->player_img)
		clean_and_exit(data, "Error\nFailed to load one or more images\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(1, "Error\nUsage: ./so_long map.ber\n", 32), 1);
	if (!has_extension_ber(argv[1]))
		return (write(1, "Error\nMap file must have .ber extension\n", 41), 1);
	ft_memset(&data, 0, sizeof(data));
	data.moves = 0;
	data.map = read_map(argv[1], &data.rows, &data.cols);
	if (!main_validate(&data))
		return (1);
	init_player(&data);
	if (!main_init_mlx(&data))
		return (write(1, "Error\nFailed to create window\n", 31), 1);
	main_load_images(&data);
	center_map(&data);
	render_map(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, handle_close, &data);
	mlx_loop(data.mlx_ptr);
	clean_and_exit(&data, NULL);
	return (0);
}
