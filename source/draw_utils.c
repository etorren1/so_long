/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:29:29 by etorren           #+#    #+#             */
/*   Updated: 2021/03/20 19:29:30 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_texture(t_win *win, t_tex *tex, int x, int y)
{
	unsigned int	color;

	color = my_mlx_pixel_get(&*tex, &*tex->addr,
			 (int)tex->pos_x, (int)tex->pos_y);
	if (color != 000000)
		my_mlx_pixel_put(&*win, x, y, color);
}

int	my_mlx_pixel_get(t_tex *tex, char *addr, int x, int y)
{
	char	*dst;
	int		color;

	dst = addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_background(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->win.h - 1 && y < all->win.h)
	{
		x = 0;
		while (x < all->win.w - 1 && x < all->win.w)
			my_mlx_pixel_put(&all->win, x++, y, 0x800BBF);
		y++;
	}
}
