#include "../include/so_long.h"

void	finish_game(t_data *data)
{
	write(1, "Congratulations!", 16);
	write(1, "\n", 2);
	clean_and_exit(data, "");
}

void	pixel_to_tile(int px, int py, int *tx, int *ty)
{
	*tx = px / TILE_SIZE;
	*ty = py / TILE_SIZE;
}

void	my_test_func(t_data *data, int new_x, int new_y)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	pixel_to_tile(new_x, new_y, &tile_x, &tile_y);
	if (tile_x >= 0 && tile_x < data->cols && tile_y >= 0
		&& tile_y < data->rows)
	{
		tile = data->map[tile_y][tile_x];
		if (tile != '1')
		{
			data->player_x = new_x;
			data->player_y = new_y;
			data->moves++;
			printf("Moves: %d\n", data->moves);
			if (tile == 'C')
			{
				data->map[tile_y][tile_x] = '0';
				data->collectibles--;
			}
			if (tile == 'E' && data->collectibles == 0)
				finish_game(data);
		}
	}
}

void	my_test_second_func(t_data *data, int keysym)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
		new_x -= TILE_SIZE;
	if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
		new_x += TILE_SIZE;
	if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
		new_y -= TILE_SIZE;
	if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
		new_y += TILE_SIZE;
	my_test_func(data, new_x, new_y);
}

int	handle_keypress(int keysym, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keysym == XK_Escape)
	{
		clean_and_exit(data, "Goodbye");
		return (0);
	}
	my_test_second_func(data, keysym);
	render_map(data);
	return (0);
}
