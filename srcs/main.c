#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	char	*err_msg;

	if (argc != 2)
	{
		fprintf(stderr, "Error\nUsage: ./so_long map.ber\n");
		return (1);
	}
	if (!has_extension_ber(argv[1]))
	{
		fprintf(stderr, "Error\nMap file must have .ber extension\n");
		return (1);
	}
	ft_memset(&data, 0, sizeof(data));
	data.moves = 0;
	data.map = read_map(argv[1], &data.rows, &data.cols);
	if (!data.map)
	{
		fprintf(stderr, "Error\nFailed to read map or map not rectangular\n");
		return (1);
	}
	err_msg = NULL;
	if (!validate_map_structure(&data, data.map, &err_msg))
	{
		fprintf(stderr, "%s\n", err_msg ? err_msg : "Error\nInvalid map");
		free_map(data.map, data.rows);
		return (1);
	}
	if (!flood_check(&data))
	{
		fprintf(stderr,
			"Error\nMap is not solvable (not all collectibles or exit reachable)\n");
		free_map(data.map, data.rows);
		return (1);
	}
	init_player(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free_map(data.map, data.rows);
		return (MLX_ERROR);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"so_long");
	if (!data.win_ptr)
	{
		free_map(data.map, data.rows);
		return (MLX_ERROR);
	}
	int w, h;
	data.background = mlx_xpm_file_to_image(data.mlx_ptr,
			"./sprites/background.xpm", &w, &h);
	data.wall = mlx_xpm_file_to_image(data.mlx_ptr, "./sprites/wall.xpm", &w,
			&h);
	data.floor = mlx_xpm_file_to_image(data.mlx_ptr, "./sprites/floor.xpm", &w,
			&h);
	data.exit_close = mlx_xpm_file_to_image(data.mlx_ptr,
			"./sprites/exit_close.xpm", &w, &h);
	data.treasure = mlx_xpm_file_to_image(data.mlx_ptr,
			"./sprites/treasure.xpm", &w, &h);
	data.exit_open = mlx_xpm_file_to_image(data.mlx_ptr, "./sprites/steps.xpm",
			&w, &h);
	data.player_img = mlx_xpm_file_to_image(data.mlx_ptr,
			"./sprites/player.xpm", &data.player_w, &data.player_h);
	if (!data.background || !data.wall || !data.floor || !data.exit_close
		|| !data.treasure || !data.exit_open || !data.player_img)
	{
		clean_and_exit(&data, "Error\nFailed to load one or more images");
	}
	center_map(&data);
	render_map(&data);
	/* Correct mlx_hook usage without casts */
	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, handle_close, &data);
	mlx_loop(data.mlx_ptr);
	/* cleanup if loop ends (shouldn't normally) */
	clean_and_exit(&data, NULL);
	return (0);
}
