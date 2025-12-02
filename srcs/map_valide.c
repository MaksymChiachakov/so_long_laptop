

#include "../include/so_long.h"

int has_extension_ber(const char *name)
{
    int len = strlen(name);
    if (len < 4) return 0;
    return ft_strcmp(name + len - 4, ".ber") == 0;
}

int validate_map_structure(t_data *data, char **map, char **err_msg)
{
    int p_count = 0, e_count = 0, c_count = 0;

    for (int y = 0; y < data->rows; y++)
    {
        if ((int)strlen(map[y]) != data->cols) { *err_msg = "Error\nMap is not rectangular"; return 0; }
        for (int x = 0; x < data->cols; x++)
        {
            char ch = map[y][x];
            if (ch == 'P') p_count++;
            else if (ch == 'E') e_count++;
            else if (ch == 'C') c_count++;
            else if (ch == '1' || ch == '0') {}
            else { *err_msg = "Error\nInvalid character in map"; return 0; }
            /* border must be walls */
            if (y == 0 || y == data->rows - 1 || x == 0 || x == data->cols - 1)
            {
                if (map[y][x] != '1') { *err_msg = "Error\nMap is not closed by walls"; return 0; }
            }
        }
    }

    if (p_count != 1) { *err_msg = "Error\nMap must contain exactly one starting position 'P'"; return 0; }
    if (e_count != 1) { *err_msg = "Error\nMap must contain exactly one exit 'E'"; return 0; }
    if (c_count < 1)  { *err_msg = "Error\nMap must contain at least one collectible 'C'"; return 0; }

    data->collectibles = c_count;
    return 1;
}
