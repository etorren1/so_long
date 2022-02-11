#include "../includes/so_long.h"

void	put_scale(t_all *all, int ybegin, int xbegin, int color)
{
	int	x;
	int	y;

	ybegin -= (int)roundf(all->win.ind_h) * SCALE;
	xbegin -= (int)roundf(all->win.ind_w) * SCALE;
	y = ybegin - 1;
	while (y++ < ybegin + SCALE)
	{
		x = xbegin - 1;
		while (x++ < xbegin + SCALE)
			my_mlx_pixel_put(&all->win, x, y, color);
	}
}

void	put_scale_without_indent(t_all *all, int ybegin, int xbegin, int color)
{
	int	x;
	int	y;

	y = ybegin - 1;
	while (y++ < ybegin + SCALE)
	{
		x = xbegin - 1;
		while (x++ < xbegin + SCALE)
			my_mlx_pixel_put(&all->win, x, y, color);
	}
}

void	put_texture(t_all *all, t_tex *tex, float ybegin, float xbegin)
{
	float		x;
	float		y;
	float	x_step;
	float	y_step;

	ybegin -= all->win.ind_h * (float)SCALE;
	xbegin -= all->win.ind_w * (float)SCALE;
	y = ybegin - 1;
	tex->pos_y = 0.0;
	x_step = (float)tex->height / (float)SCALE;
	y_step = (float)tex->width / (float)SCALE;
	while (y++ < ybegin + SCALE)
	{
		x = xbegin - 1;
		tex->pos_x = 0.0;
		while (x++ < xbegin + SCALE)
		{
			draw_texture(&all->win, tex, x, y);
			tex->pos_x += x_step;
		}
		tex->pos_y += y_step;
	}
}
