
#include "../includes/so_long.h"

void	clean_exit(t_all *all, int id)
{
	int	i;

	i = 0;
	if (all->map)
	{
		while (all->map[i])
			free(all->map[i++]);
		free(all->map);
	}
	if (all->steps > 0)
		printf("TOTAL_SCORE=%d\n", all->score * 10000 / all->steps);
	exit(id);
}

int	window_exit(t_all *all)
{
	clean_exit(all, 0);
	return (0);
}

void	error(t_all *all, int err_id)
{
	if (err_id == 1)
		ft_putstr_fd("\033[31mERROR:\033[0m\n\
Bad spawn point initialization\n", 2);
	if (err_id == 2)
		ft_putstr_fd("\033[31mERROR:\033[0m\nNot enough E or C points\n", 2);
	if (err_id == 3)
		ft_putstr_fd("\033[31mERROR:\033[0m\nInvalid path to texture\n", 2);
	if (err_id == 4)
		ft_putstr_fd("\033[31mERROR:\033[0m\n\
Bad resolution initialization\n", 2);
	if (err_id == 5)
		ft_putstr_fd("\033[31mERROR:\033[0m\nCan't open map\n", 2);
	if (err_id == 6)
		ft_putstr_fd("\033[31mERROR:\033[0m\nInvalid map initialization\n", 2);
	if (err_id == 7)
		ft_putstr_fd("Error\nCannot create bmp file", 2);
	if (err_id == 8)
		ft_putstr_fd("\033[31mERROR:\033[0m\nResolution OVER_9000\n", 2);
	if (err_id == 9)
		ft_putstr_fd("\033[31mERROR:\033[0m\nBad arguments\n", 2);
	if (err_id == 10)
		ft_putstr_fd("\033[31mERROR:\033[0m\nBad config initialization\n", 2);
	clean_exit(all, err_id);
}
