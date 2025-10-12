#include "../../include/header.h"

bool	validate_lines_aux(t_map *map, int *i, int *j)
{
	while (map->gamemap[*i][*j] != '\0')
	{
		if (map->gamemap[*i][*j] != ' ' && map->gamemap[*i][*j] != '0'
			&& map->gamemap[*i][*j] != '1' && map->gamemap[*i][*j] != 'N'
			&& map->gamemap[*i][*j] != 'S' && map->gamemap[*i][*j] != 'E'
			&& map->gamemap[*i][*j] != 'W')
		{
			return (false);
		}
		if (map->gamemap[*i][*j] == ' ')
		{
			if (validate_lines2(map, *i, *j) == false)
				return (false);
		}
		(*j)++;
	}
  return true;
}
