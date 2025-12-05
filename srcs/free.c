#include "../include/so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_images(t_data *data)
{
	if (!data || !data->mlx_ptr)
		return ;
	if (data->background)
		mlx_destroy_image(data->mlx_ptr, data->background);
	if (data->wall)
		mlx_destroy_image(data->mlx_ptr, data->wall);
	if (data->exit_close)
		mlx_destroy_image(data->mlx_ptr, data->exit_close);
	if (data->exit_open)
		mlx_destroy_image(data->mlx_ptr, data->exit_open);
	if (data->treasure)
		mlx_destroy_image(data->mlx_ptr, data->treasure);
	if (data->floor)
		mlx_destroy_image(data->mlx_ptr, data->floor);
	if (data->player_img)
		mlx_destroy_image(data->mlx_ptr, data->player_img);
}

void	clean_and_exit(t_data *data, const char *msg)
{
	size_t	len;

	if (msg)
	{
		len = ft_strlen(msg);
		if (ft_strncmp(msg, "Error", 5) == 0)
			write(1, msg, len);
		write(1, "\n", 2);
	}
	if (data)
	{
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_images(data);
		free_map(data->map, data->rows);
	}
	if (msg && ft_strncmp(msg, "Error", 5) == 0)
		exit(1);
	else
		exit(0);
}
// exit((msg && strncmp(msg, "Error", 5) == 0) ? 1 : 0);