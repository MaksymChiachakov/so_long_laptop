
#include "../include/so_long.h"

int flood_check(t_data *data)
{
    int rows = data->rows, cols = data->cols;
    char **copy = malloc(sizeof(char*) * rows);
    if (!copy) return 0;
    for (int i = 0; i < rows; i++)
    {
        copy[i] = ft_strdup(data->map[i]);
        if (!copy[i])
        {
            for (int j = 0; j < i; j++) free(copy[j]);
            free(copy);
            return 0;
        }
    }

    /* find P */
    int sx = -1, sy = -1;
    for (int y = 0; y < rows && sx == -1; y++)
        for (int x = 0; x < cols; x++)
            if (copy[y][x] == 'P') { sx = x; sy = y; break; }

    if (sx == -1) { for (int i = 0; i < rows; i++) free(copy[i]); free(copy); return 0; }

    /* simple BFS using a queue (array-based) */
    int capacity = rows * cols + 10;
    t_pt *queue = malloc(sizeof(t_pt) * capacity);
    if (!queue) { free_map(copy, rows); return 0; }
    int head = 0, tail = 0;
    queue[tail++] = (t_pt){sx, sy};
    copy[sy][sx] = 'X'; /* mark visited */

    while (head < tail)
    {
        t_pt cur = queue[head++];
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        for (int k = 0; k < 4; k++)
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;
            if (copy[ny][nx] == '1' || copy[ny][nx] == 'X') continue;
            /* walkable: 0, C, E, P */
            queue[tail++] = (t_pt){nx, ny};
            copy[ny][nx] = 'X';
        }
    }

    /* now check all C and E visited */
    int ok = 1;
    for (int y = 0; y < rows && ok; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (data->map[y][x] == 'C' && copy[y][x] != 'X') { ok = 0; break; }
            if (data->map[y][x] == 'E' && copy[y][x] != 'X') { ok = 0; break; }
        }
    }

    free(queue);
    for (int i = 0; i < rows; i++) free(copy[i]);
    free(copy);
    return ok;
}
