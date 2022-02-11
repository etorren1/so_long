
#include "../includes/so_long.h"

static int	check_args(int ac, char **av)
{
	size_t	len;
	int		res;

	res = 0;
	if (ac > 1 && ac < 3)
	{
		len = ft_strlen(av[1]);
		if (len >= 4 && av[1][len - 1] == 'r' && av[1][len - 2] == 'e'\
			&& av[1][len - 3] == 'b' && av[1][len - 4] == '.')
			res = 1;
		else
			res = 0;
	}
	return (res);
}

void	new_img(t_all *all)
{
	fill_background(all);
	draw_back(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
}

void	get_cam_pos(t_all *all)
{
	int	res_w;
	int	res_h;

	//my_get_screen_size(&res_w, &res_h); // macOS
	//mlx_get_screen_size(all->win.mlx, &res_w, &res_h); // linux
	
	if (res_w < all->win.w)
		all->win.w = res_w - (res_w % SCALE);
	if (res_h < all->win.h)
		all->win.h = res_h - (res_h % SCALE);
	all->win.w = 800 - 800 % SCALE;
	all->win.h = 600 - 600 % SCALE;
	printf("res_w=%d res_h=%d\n", all->win.w, all->win.h);
	if (all->plr.pos_y > all->win.h / SCALE / 2)
		all->win.ind_h = all->plr.pos_y - all->win.h / SCALE / 2;
	if (all->plr.pos_x > all->win.w / SCALE / 2)
		all->win.ind_w = all->plr.pos_x - all->win.w / SCALE / 2;
}

void	new_window(t_all *all)
{
	get_cam_pos(all);
	all->win.mlx = mlx_init();
	// if (!all->win.mlx)
	// {
	// 	printf("mlx_init error\n");
	// 	exit(1);
	// }
	all->win.win = mlx_new_window(all->win.mlx, all->win.w,
			 all->win.h, "rougelike");
	all->win.img = mlx_new_image(all->win.mlx, all->win.w,
			 all->win.h);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bits_per_pixel,
			 &all->win.line_length, &all->win.endian);
	get_textures(all);
	new_img(all);
}

int	main(int argc, char **argv)
{
	int		args;
	t_all	*all;

	if (argc < 2)
		return (ft_putstr_fd("\033[31mERROR:\033[0m\nNot map file\n", 2));
	args = check_args(argc, argv);
	all = malloc(sizeof(t_all));
	if (args)
	{
		parser(argv[1], all);
		all->start_time = clock();
		new_window(all);
		mlx_hook(all->win.win, 2, (1L << 0), key_press, all);
		mlx_hook(all->win.win, 3, (1L << 1), key_unpress, all);
		mlx_loop_hook(all->win.mlx, core, all);
		mlx_loop(all->win.mlx);
	}
	else
		return (ft_putstr_fd("\033[31mERROR:\033[0m\nBad arguments\n", 2));
	return (0);
}
