#include "../include/so_long.h"

int player_animation(t_data *data)
{
    static int counter = 0;

    if (!data->is_moving)
        return (0);

    // ralentir l’animation
    counter++;
    if (counter < 6)
        return (0);
    counter = 0;

    // passer à la frame suivante
    data->frame++;
    if (data->frame > 3)
        data->frame = 0;

    // redessiner la map + le joueur
    my_new_best_func(data);

    put_image_with_transparency(data,
        data->player_img[data->frame],
        data->offset_x + data->player_x,
        data->offset_y + data->player_y);

    return (0);
}
