
#include "../includes/so_long.h"

int	cases(int i, int j, char **map, int size)
{
	if (i == 0 || j == 0 || i == size || j >= (int)ft_strlen(map[i]) - 1
		 || !ft_strchr("01PECBSe", map[i - 1][j - 1])
		 || !ft_strchr("01PECBSe", map[i][j + 1])
		 || !ft_strchr("01PECBSe", map[i - 1][j])
		 || !ft_strchr("01PECBSe", map[i - 1][j + 1])
		 || !ft_strchr("01PECBSe", map[i][j - 1])
		 || !ft_strchr("01PECBSe", map[i + 1][j + 1])
		 || !ft_strchr("01PECBSe", map[i + 1][j - 1])
		 || !ft_strchr("01PECBSe", map[i + 1][j])
		 || !map[i - 1][j - 1] || !map[i][j + 1]
		 || !map[i - 1][j] || !map[i - 1][j + 1]
		 || !map[i][j - 1] || !map[i + 1][j + 1]
		 || !map[i + 1][j - 1] || !map[i + 1][j])
		return (1);
	return (0);
}

void	check_map(t_all *all, int size, int exit, int collect)
{
	int	i;
	int	j;

	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (ft_strchr("0PECBSe", all->map[i][j]))
			{
				if (cases(i, j, &*all->map, size))
					error(all, 6);
			}
			else if (all->map[i][j] != '1')
				error(all, 6);
			if (all->map[i][j] == 'E')
				exit++;
			if (all->map[i][j] == 'C')
				collect++;
		}
	}
	if (exit == 0 || collect == 0)
		error(all, 2);
}

void	get_resolution(t_all *all, t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	all->win.h = ft_lstsize(temp) * SCALE;
	all->map_size_y = all->win.h / SCALE;
	all->win.w = 0;
	while (temp)
	{
		if (all->win.w < (int)ft_strlen(temp->content))
			all->win.w = (int)ft_strlen(temp->content);
		temp = temp->next;
	}
	all->map_size_x = all->win.w;
	all->win.w *= SCALE;
}

int	empty_string(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (0);
	return (1);
}
