#include "../include/so_long.h"

void	init_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x * TILE_SIZE;
				data->player_y = y * TILE_SIZE;
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
