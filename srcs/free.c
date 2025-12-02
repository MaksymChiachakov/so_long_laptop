#include "../include/so_long.h"


/* ---------- utility: error + cleanup ---------- */

void    free_map(char **map, int rows)
{
    if (!map) return;
    for (int i = 0; i < rows; i++)
    {
        free(map[i]);
    }
    free(map);
}

void    free_images(t_data *data)
{
    if (!data || !data->mlx_ptr) return;
    if (data->background) mlx_destroy_image(data->mlx_ptr, data->background);
    if (data->wall) mlx_destroy_image(data->mlx_ptr, data->wall);
    if (data->exit_close) mlx_destroy_image(data->mlx_ptr, data->exit_close);
    if (data->exit_open) mlx_destroy_image(data->mlx_ptr, data->exit_open);
    if (data->treasure) mlx_destroy_image(data->mlx_ptr, data->treasure);
    if (data->floor) mlx_destroy_image(data->mlx_ptr, data->floor);
    if (data->player_img) mlx_destroy_image(data->mlx_ptr, data->player_img);
}

void    clean_and_exit(t_data *data, const char *msg)
{
    if (msg)
    {
        if (strncmp(msg, "Error", 5) == 0)
            fprintf(stderr, "%s\n", msg);
        else
            printf("%s\n", msg);
    }
    if (data)
    {
        if (data->win_ptr)
            mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free_images(data);
        free_map(data->map, data->rows);
    }
    exit((msg && strncmp(msg, "Error", 5) == 0) ? 1 : 0);
}
