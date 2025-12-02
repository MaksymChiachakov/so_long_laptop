

#include "../include/so_long.h"

/* ---------- centering & render ---------- */

void center_map(t_data *data)
{
    int map_width = data->cols * TILE_SIZE;
    int map_height = data->rows * TILE_SIZE;

    data->offset_x = (WINDOW_WIDTH - map_width - 500) / 2;
    data->offset_y = (WINDOW_HEIGHT - map_height - 400) / 2;

    if (data->offset_x < 0) data->offset_x = 0;
    if (data->offset_y < 0) data->offset_y = 0;
}

void render_background(t_data *data)
{
    for (int y = 0; y < WINDOW_HEIGHT; y += TILE_SIZE)
    {
        for (int x = 0; x < WINDOW_WIDTH; x += TILE_SIZE)
        {
            mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
                data->background, x, y);
        }
    }
}

void render_map(t_data *data)
{
    render_background(data);

    for (int y = 0; y < data->rows; y++)
    {
        for (int x = 0; x < data->cols; x++)
        {
            char c = data->map[y][x];
            int px = data->offset_x + x * TILE_SIZE;
            int py = data->offset_y + y * TILE_SIZE;

            if (c == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall, px, py);
            else
            {
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor, px, py);
                if (c == 'E')
                {
                    /* if collectibles remain, show closed exit, else open */
                    if (data->collectibles > 0)
                        put_image_with_transparency(data, data->exit_close, data->player_w, data->player_h, px, py);
                    else
                        put_image_with_transparency(data, data->exit_open, data->player_w, data->player_h, px, py);
                }
                else if (c == 'C')
                {
                    put_image_with_transparency(data, data->treasure, data->player_w, data->player_h, px, py);
                }
            }
        }
    }

    /* draw player last */
    put_image_with_transparency(data, data->player_img, data->player_w, data->player_h,
                            data->offset_x + data->player_x, data->offset_y + data->player_y);
}
