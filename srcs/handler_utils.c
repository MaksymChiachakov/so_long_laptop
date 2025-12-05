#include "../include/so_long.h"

int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_and_exit(data, "");
	return (0);
}
