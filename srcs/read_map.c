
#include "../include/so_long.h"

char	**read_map(const char *filename, int *rows, int *cols)
{
	FILE *file = fopen(filename, "r");
	if (!file)
		return NULL;

	char **map = NULL;
	char *line = NULL;
	size_t cap = 0;
	ssize_t len;
	int r = 0;
	int width = -1;

	/* use getline for arbitrary length lines */
	while ((len = getline(&line, &cap, file)) != -1)
	{
		if (len > 0 && line[len-1] == '\n')
		{
			line[len-1] = '\0';
			len--;
		}
		if (width == -1)
			width = (int)len;
		else if ((int)len != width)
		{
			free(line);
			free_map(map, r);
			fclose(file);
			return NULL; /* non-rectangular */
		}
		char *row = malloc((size_t)len + 1);
		if (!row)
		{
			free(line);
			free_map(map, r);
			fclose(file);
			return NULL;
		}
		ft_strcpy(row, line);
		char **tmp = realloc(map, sizeof(char*) * (r + 1));
		if (!tmp)
		{
			free(row);
			free(line);
			free_map(map, r);
			fclose(file);
			return NULL;
		}
		map = tmp;
		map[r] = row;
		r++;
	}
	free(line);
	fclose(file);

	if (r == 0)
	{
		free_map(map, r);
		return NULL;
	}

	*rows = r;
	*cols = width;
	return map;
}
