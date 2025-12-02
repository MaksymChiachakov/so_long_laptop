#include "../include/so_long.h"

/* ---------- game mechanics: movement handling ---------- */

void    finish_game(t_data *data)
{
    printf("Congratulations! You escaped in %d moves!\n", data->moves);
    clean_and_exit(data, "Goodbye");
}

/* convert pixel coords to tile coords */
void pixel_to_tile(int px, int py, int *tx, int *ty)
{
    *tx = px / TILE_SIZE;
    *ty = py / TILE_SIZE;
}

/* NOTE: signature changed to be compatible with mlx_hook:
   KeyPress/KeyRelease handlers on many MLX versions receive (int keycode, void *param)
*/
int handle_keypress(int keysym, void *param)
{
    t_data *data = (t_data *)param;

    if (keysym == XK_Escape)
    {
        clean_and_exit(data, "Goodbye");
        return 0;
    }

    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
        new_x -= TILE_SIZE;
    if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
        new_x += TILE_SIZE;
    if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
        new_y -= TILE_SIZE;
    if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
        new_y += TILE_SIZE;

    int tile_x, tile_y;
    pixel_to_tile(new_x, new_y, &tile_x, &tile_y);

    if (tile_x >= 0 && tile_x < data->cols &&
        tile_y >= 0 && tile_y < data->rows)
    {
        char tile = data->map[tile_y][tile_x];
        if (tile != '1') /* not a wall */
        {
            /* move */
            data->player_x = new_x;
            data->player_y = new_y;
            data->moves++;
            printf("Moves: %d\n", data->moves);

            /* collectible */
            if (tile == 'C')
            {
                data->map[tile_y][tile_x] = '0';
                data->collectibles--;
            }
            /* exit */
            if (tile == 'E' && data->collectibles == 0)
            {
                finish_game(data);
            }
        }
    }

    render_map(data);
    return 0;
}

/* handle window close (click X) — signature compatible with mlx_hook */
int handle_close(void *param)
{
    t_data *data = (t_data *)param;
    clean_and_exit(data, "Goodbye");
    return 0;
}
