
#include "../include/so_long.h"

void	init_player(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->rows)
	{
		int	x;

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

void	put_image_with_transparency(t_data *data, void *img, int img_w,
		int img_h, int x_pos, int y_pos)
{
	char	*addr;
	int		transparent_color;
	int		*pixel;

	int bpp, size_line, endian;
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	transparent_color = 0xFF00FF;
	for (int j = 0; j < img_h; j++)
	{
		for (int i = 0; i < img_w; i++)
		{
			pixel = (int *)(addr + j * size_line + i * (bpp / 8));
			if (*pixel != transparent_color)
			{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x_pos + i, y_pos
					+ j, *pixel);
			}
		}
	}
}
