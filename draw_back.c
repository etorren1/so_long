
#include "includes/so_long.h"

static void	cases(t_all *all, int y, int x)
{
	if (ft_strchr("0PCEBDSe", all->map[y][x]))
		put_scale(&*all, y * SCALE, x * SCALE,
			0x2C2738); //2C2738 / 00000F
	if (y > 0 && ft_strchr("1", all->map[y - 1][x]))
		put_texture(all, &all->tex.sidewall, y * SCALE, x * SCALE);
	if (ft_strchr("1", all->map[y][x]))
		put_texture(all, &all->tex.topwall, y * SCALE, x * SCALE);
	else if (ft_strchr("E", all->map[y][x]))
		put_texture(all, &all->tex.exit, y * SCALE, x * SCALE);
	else if (ft_strchr("C", all->map[y][x]))
		put_texture(all, &all->tex.sprite, y * SCALE, x * SCALE);
}

static void	deadbanner(t_all *all, int y, int x)
{
	put_texture(all, &all->tex.dieban[0], (y + 1) * SCALE, (x - 1) * SCALE);
	put_texture(all, &all->tex.dieban[1], (y + 1) * SCALE, (x) * SCALE);
	put_texture(all, &all->tex.dieban[2], (y + 1) * SCALE, (x + 1) * SCALE);
}

static void draw_direction(t_all *all, float y, float x)
{
	if (all->plr.dir_y == 1)
		put_texture(all, &all->tex.bwalk[1], y * SCALE, x * SCALE);
	else if (all->plr.dir_y == -1)
		put_texture(all, &all->tex.twalk[1], y * SCALE, x * SCALE);
	else if (all->plr.dir_x == 1)
		put_texture(all, &all->tex.rwalk[1], y * SCALE, x * SCALE);
	else if (all->plr.dir_x == -1)
		put_texture(all, &all->tex.lwalk[1], y * SCALE, x * SCALE);
}


static void	events(t_all *all, float y, float x, int i)
{
	if (all->plr.action == 'l')
		put_texture(all, &all->tex.lwalk[i], y * SCALE, x * SCALE);
	else if (all->plr.action == 'r')
		put_texture(all, &all->tex.rwalk[i], y * SCALE, x * SCALE);
	else if (all->plr.action == 't')
		put_texture(all, &all->tex.twalk[i], y * SCALE, x * SCALE);
	else if (all->plr.action == 'b')
		put_texture(all, &all->tex.bwalk[i], y * SCALE, x * SCALE);
	else if (all->plr.action == 'd')
	{
		put_texture(all, &all->tex.dead[(int)all->plr.dtime], y * SCALE, x * SCALE);
		if ((int)all->plr.dtime == 7)
		{
			usleep(5000000);
			printf("\e[36mYOU_DIED!\e[0m\n");
			clean_exit(all, 0);
		}
		all->plr.dtime += 0.15;
		deadbanner(all, y + 0.02, x + 0.02);
	}
	else if (all->plr.action == 'n')
		draw_direction(all, y, x);
	else if (all->plr.action == 'a')
	{
		draw_direction(all, y, x);
		put_texture(all, &all->tex.dead[(int)all->plr.atime], (y + all->plr.dir_y) * SCALE, (x + all->plr.dir_x) * SCALE);
		all->plr.atime += 0.15;
		if ((int)all->plr.atime == 7)
		{
			all->plr.action = 'n';
			all->plr.atime = 0.0;
		}
	}
	if (all->obj.action == '1')
		put_texture(all, &all->tex.box, all->obj.pos_y * SCALE, all->obj.pos_x * SCALE);
}

static void	events_en(t_all *all, float y, float x, int i, int l)
{
	if (all->enem[l].action == 'l')
	{
		put_texture(all, &all->tex.lwalk[i], y * SCALE, x * SCALE);
		all->enem[l].laststep = &all->tex.lwalk[1];
	}
	else if (all->enem[l].action == 'r')
	{
		put_texture(all, &all->tex.rwalk[i], y * SCALE, x * SCALE);
		all->enem[l].laststep = &all->tex.rwalk[1];
	}
	else if (all->enem[l].action == 't')
	{
		put_texture(all, &all->tex.twalk[i], y * SCALE, x * SCALE);
		all->enem[l].laststep = &all->tex.twalk[1];
	}
	else if (all->enem[l].action == 'b')
	{
		put_texture(all, &all->tex.bwalk[i], y * SCALE, x * SCALE);
		all->enem[l].laststep = &all->tex.bwalk[1];
	}
	else if (all->enem[l].action == 'n')
		put_texture(all, all->enem[l].laststep, y * SCALE, x * SCALE);
	else if (all->enem[l].action == 'd')
		put_texture(all, &all->tex.dead[3], y * SCALE, x * SCALE);
}

void	draw_back(t_all *all)
{
	int	x;
	int	y;
	int	i;

	y = -1 + all->win.ind_h;
	while (all->map[++y] && y < all->win.h / SCALE + all->win.ind_h)
	{
		x = -1 + all->win.ind_w;
		while (all->map[y][++x] && x < all->win.w / SCALE + all->win.ind_w)
			cases(all, y, x);
	}
	// static_obj draw
	i = -1;
	while (++i < all->spears_count)
	{
		if (all->spears[i].pos_y >= all->win.ind_h && all->spears[i].pos_y < all->win.ind_h + all->win.h / SCALE
		 && all->spears[i].pos_x >= all->win.ind_w && all->spears[i].pos_x < all->win.ind_w + all->win.w / SCALE)
		{
			if (all->spears[i].status == 'n')
			{
				if (all->spears[i].pos_y == (int)roundf(all->plr.pos_y) && all->spears[i].pos_x == (int)roundf(all->plr.pos_x)
					&& !round100(all->plr.pos_x) && !round100(all->plr.pos_y))
					all->plr.action = 'd';
				else
					put_texture(all, &all->tex.spear, all->spears[i].pos_y * SCALE, all->spears[i].pos_x * SCALE);
			}
			else if (all->spears[i].status == 'b')
				put_texture(all, &all->tex.bspear, all->spears[i].pos_y * SCALE, all->spears[i].pos_x * SCALE);
		}
	}
	/// enemy
	
	int l = -1;
	while (++l < 4) {
	i = all->enem[l].steps % 4;
	if ((int)all->enem[l].pos_y >= all->win.ind_h && (int)all->enem[l].pos_y < all->win.ind_h + all->win.h / SCALE - 1
		 && (int)all->enem[l].pos_x >= all->win.ind_w && (int)all->enem[l].pos_x < all->win.ind_w + all->win.w / SCALE - 1)
	{
		if (i == 0)
			events_en(all, all->enem[l].pos_y, all->enem[l].pos_x, i, l);
		else if (i == 1)
			events_en(all, all->enem[l].pos_y, all->enem[l].pos_x, i, l);
		else if (i == 2)
			events_en(all, all->enem[l].pos_y, all->enem[l].pos_x, i, l);
		else
			events_en(all, all->enem[l].pos_y, all->enem[l].pos_x, i, l);
	}
	}
	/// !
	// draw events
	i = all->steps % 4;
	events(all, all->plr.pos_y, all->plr.pos_x, i);
	// draw first plane 
	y = -1 + all->win.ind_h;
	while (all->map[++y] && y < all->win.h / SCALE + all->win.ind_h)
	{
		x = -1 + all->win.ind_w;
		while (all->map[y][++x] && x < all->win.w / SCALE + all->win.ind_w)
		{
			if (ft_strchr("B", all->map[y][x]))
				put_texture(all, &all->tex.box, y * SCALE, x * SCALE);
		}
	}
}
