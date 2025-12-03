#include "../include/so_long.h"

void	bfs_run(char **copy, t_pt *queue, int rows, int cols)
{
	int		head;
	int		tail;
	t_pt	cur;

	head = 0;
	tail = 1;
	while (head < tail)
	{
		cur = queue[head++];
		process_neighbors(copy, cur, queue, &tail, rows, cols);
	}
}

int	flood_verify(char **copy, char **map, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if ((map[y][x] == 'C' || map[y][x] == 'E') && copy[y][x] != 'X')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	flood_check(t_data *data)
{
	char	**copy;
	t_pt	*queue;
	t_size size;
	int		sx;
	int		sy;

	size.rows = data->rows;
	size.cols = data->cols;
	copy = copy_map(data->map, data->rows);
	if (!copy)
		return (0);
	if (!find_player(copy, size, &sx, &sy))
		return (free_map(copy, data->rows), 0);
	queue = malloc(sizeof(t_pt) * (data->rows * data->cols + 1));
	if (!queue)
		return (free_map(copy, data->rows), 0);
	queue[0] = (t_pt){sx, sy};
	copy[sy][sx] = 'X';
	bfs_run(copy, queue, data->rows, data->cols);
	free(queue);
	if (!flood_verify(copy, data->map, data->rows, data->cols))
		return (free_map(copy, data->rows), 0);
	free_map(copy, data->rows);
	return (1);
}
