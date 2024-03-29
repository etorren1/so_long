
#include "../includes/so_long.h"

int	key_press(int key, t_all *all)
{
	// printf("key = %d\n", key);
	if (key == 13 || key == 1731 || key == 119) //119 /1731
		all->key.w = '1';
	if (key == 1 || key == 1753 || key == 115) //115 /1753
		all->key.s = '1';
	if (key == 0 || key == 1734 || key == 97) //97 /1734
		all->key.a = '1';
	if (key == 2 || key == 1751 || key == 100) //100 /1751
		all->key.d = '1';
	if (key == 3 || key == 102 || key == 1729)
		all->key.f = '1';
	if (key == 53 || key == 65307)
		clean_exit(all, 0);
	return (key);
}

int	key_unpress(int key, t_all *all)
{
	if (key == 13 || key == 1731 || key == 119) //119 /1731
		all->key.w = '0';
	if (key == 1 || key == 1753 || key == 115) //115 /1753
		all->key.s = '0';
	if (key == 0 || key == 1734 || key == 97) //97 /1734
		all->key.a = '0';
	if (key == 2 || key == 1751 || key == 100) //100 /1751
		all->key.d = '0';
	if (key == 3 || key == 102 || key == 1729)
		all->key.f = '0';
	return (key);
}


int	round100(float	pos)
{
	int	roundpos;

	roundpos = (int)roundf(pos * 100.0) % 100;
	if (roundpos % 5)
		roundpos++;
	return (roundpos);
}

int	round10(float	pos)
{
	int	roundpos;

	roundpos = (int)roundf(pos * 10.0) % 10;
	if (roundpos % 5)
		roundpos++;
	return (roundpos);
}


int check_pos(char **map, float pos_y, float pos_x, char ch)
{
	if (map[(int)roundf(pos_y)][(int)roundf(pos_x)] == ch
		 && !round100(pos_y) && !round100(pos_x))
		 return (1);
	return (0);
}

void	take_coin(t_all *all)
{
	if (check_pos(all->map, all->plr.pos_y, all->plr.pos_x, 'C'))
	{
		all->map[(int)roundf(all->plr.pos_y)][(int)roundf(all->plr.pos_x)] = '0';
		all->score++;
	}
	if (check_pos(all->map, all->plr.pos_y, all->plr.pos_x, 'E'))
		clean_exit(all, 0);
	if (check_pos(all->map, all->plr.pos_y + all->plr.dir_y - SPEED * all->plr.dir_y, 
					all->plr.pos_x + all->plr.dir_x - SPEED * all->plr.dir_x, 'B'))
	{
		all->obj.pos_x = all->plr.pos_x + (float)all->plr.dir_x;
		all->obj.pos_y = all->plr.pos_y + (float)all->plr.dir_y;
		all->obj.action = '1';
		all->obj.type = 'B';
		all->obj.oldplraction = all->plr.action;
		all->map[(int)roundf(all->plr.pos_y + all->plr.dir_y)][(int)roundf(all->plr.pos_x + all->plr.dir_x)] = '0';
	}
	else if (all->obj.action == '1')
	{
		all->obj.pos_x += SPEED * all->plr.dir_x;
		all->obj.pos_y += SPEED * all->plr.dir_y;
	}
	if (all->obj.action == '1' && all->obj.oldplraction != all->plr.action)
	{
		all->map[(int)roundf(all->obj.pos_y)][(int)roundf(all->obj.pos_x)] = 'B';
		all->obj.action = '0';
	}
	if (check_pos(all->map, all->obj.pos_y + SPEED  * all->plr.dir_y, all->obj.pos_x + SPEED * all->plr.dir_x, 'S'))
	{
		
		int i;

		i = -1;
		while (++i < all->spears_count)
		{
			if ((int)roundf(all->obj.pos_y) == all->spears[i].pos_y
			 && (int)roundf(all->obj.pos_x) == all->spears[i].pos_x)
			 {
				all->spears[i].status = 'b';
				break ;
			 }
		}
	}
}

void	autostep(t_all *all)
{
	int	x_pos;
	int	y_pos;

	x_pos = round100(all->plr.pos_x);
	y_pos = round100(all->plr.pos_y);
	if (x_pos)
	{
		if (all->plr.dir_x == 1)
		{
			all->plr.pos_x += SPEED;
			all->plr.action = 'r';
		}
		else if (all->plr.dir_x == -1)
		{
			all->plr.pos_x -= SPEED;
			all->plr.action = 'l';
		}
	}
	else if (y_pos)
	{
		if (all->plr.dir_y == 1)
		{
			all->plr.pos_y += SPEED;
			all->plr.action = 'b';
		}
		else if (all->plr.dir_y == -1)
		{
			all->plr.pos_y -= SPEED;
			all->plr.action = 't';
		}
	}
	else
	{
		all->plr.pos_x = roundf(all->plr.pos_x);
		all->plr.pos_y = roundf(all->plr.pos_y);
		all->plr.h_move = '0';
		all->plr.v_move = '0';
		all->plr.action = 'n';
	}
}

void	steps(float x, float y, int *steps, char action)
{
	int	x_pos;
	int	y_pos;

	x_pos = round100(x);
	y_pos = round100(y);
	if (!(x_pos % 25) && (action == 'r' || action == 'l'))
		(*steps)++;
	if (!(y_pos % 25) && (action == 't' || action == 'b'))
		(*steps)++;
}

void	movecam(t_all *all)
{
	if ((int)roundf(all->plr.pos_y) - all->win.ind_h == 1)
	{
		all->win.ind_h -= all->win.h / SCALE / 3;
		if (all->win.ind_h < 0)
			all->win.ind_h = 0;
	}
	if ((int)roundf(all->plr.pos_y) - all->win.ind_h == all->win.h / SCALE - 2)
	{
		all->win.ind_h += all->win.h / SCALE / 3;
		if (all->win.ind_h > all->map_size_y - all->win.h / SCALE)
			all->win.ind_h = all->map_size_y - all->win.h / SCALE;
	}
	if ((int)roundf(all->plr.pos_x) - all->win.ind_w == all->win.w / SCALE - 2)
	{
		all->win.ind_w += all->win.w / SCALE / 3;
		if (all->win.ind_w > all->map_size_x - all->win.w / SCALE)
			all->win.ind_w = all->map_size_x - all->win.w / SCALE;
	}
	if ((int)roundf(all->plr.pos_x) - all->win.ind_w == 1)
	{
		all->win.ind_w -= all->win.w / SCALE / 3;
		if (all->win.ind_w < 0)
			all->win.ind_w = 0;
	}
}

t_node    *pathfind(char **map, t_enemy *en, float x_end, float y_end);

static int    blocked(int l, t_enemy ena[4], float x, float y)
{
	t_enemy *en = &ena[l];
	int i = -1;
	while (++i < 4)
	{
		if (i != l && ena[i].action != 'd')
		{
			if (roundf(en->pos_x + x) == roundf(ena[i].pos_x)
		 	 && roundf(en->pos_y + y) == roundf(ena[i].pos_y))
			 	return (1);
		}
	}
	return (0);
}

void	move_enemy(int i, t_enemy ena[4], t_plr *plr)
{
	t_enemy *en = &ena[i];
	t_node *way = en->way;

	if (way && en->action != 'a')
	{
		if (en->going == '0')
		{
			en->going = '1';
			en->pos1 = way->content;
			en->pos2 = way->next->content;
			if (en->pos1->x < en->pos2->x && !blocked(i, ena, 1, 0) && !blocked(i, ena, 1, 1))
				en->action = 'r';
			else if (en->pos1->x > en->pos2->x && !blocked(i, ena, -1, 0) && !blocked(i, ena, -1, -1))
				en->action = 'l';
			else if (en->pos1->y > en->pos2->y && !blocked(i, ena, 0, -1) && !blocked(i, ena, 1, -1))
				en->action = 't';
			else if (en->pos1->y < en->pos2->y && !blocked(i, ena, 0, 1) && !blocked(i, ena, -1, 1))
				en->action = 'b';
			else
				en->action = 'n';
		}
		steps(en->pos_x, en->pos_y, &en->steps, en->action);
		if (en->action == 'r')
			en->pos_x += 0.04;
		else if (en->action == 'l')
			en->pos_x -= 0.04;
		else if (en->action == 't')
			en->pos_y -= 0.04;
		else if (en->action == 'b')
			en->pos_y += 0.04;
		if (!round100(en->pos_y) && !round100(en->pos_x) && en->going == '1')
		{
			en->dir_x = 0;
			en->dir_y = 0;
			if (roundf(en->pos_y) == roundf(plr->pos_y))
			{
				if (en->pos_x < plr->pos_x)
					en->dir_x = 1;
				else if (en->pos_x > plr->pos_x)
					en->dir_x = -1;
			}
			else if (roundf(en->pos_x) == roundf(plr->pos_x))
			{
				if (en->pos_y < plr->pos_y)
					en->dir_y = 1;
				else if (en->pos_y > plr->pos_y)
					en->dir_y = -1;
			}
			en->going = '0';
			en->pos_y = roundf(en->pos_y);
			en->pos_x = roundf(en->pos_x);
		}
	}
}

static int	plr_distance(t_plr *plr, float x2, float y2, float dist)
{
	if (plr->pos_y == y2)
	{
		if (plr->dir_x == -1)
			if (x2 > plr->pos_x - dist && x2 < plr->pos_x)
				return (1);
		if (plr->dir_x == 1)
			if (x2 > plr->pos_x && x2 < plr->pos_x + dist)
				return (1);
	}
	if (plr->pos_x == x2)
	{
		if (plr->dir_y == -1)
			if (y2 > plr->pos_y - dist && y2 < plr->pos_y)
				return (1);
		if (plr->dir_y == 1)
			if (y2 > plr->pos_y && y2 < plr->pos_y + dist)
				return (1);
	}
	return (0);
}

static int	en_distance(t_enemy *en, float x2, float y2, float dist)
{
	if (en->pos_y == y2)
	{
		if (en->dir_x == -1)
			if (x2 > en->pos_x - dist && x2 < en->pos_x)
				return (1);
		if (en->dir_x == 1)
			if (x2 > en->pos_x && x2 < en->pos_x + dist)
				return (1);
	}
	if (en->pos_x == x2)
	{
		if (en->dir_y == -1)
			if (y2 > en->pos_y - dist && y2 < en->pos_y)
				return (1);
		if (en->dir_y == 1)
			if (y2 > en->pos_y && y2 < en->pos_y + dist)
				return (1);
	}
	return (0);
}

void	attack(t_all *all)
{
	int l = -1;
	if (all->key.f == '1' && all->plr.action != 'a' && all->obj.action != '1')
	{
		all->plr.action = 'a';
		while (++l < 4)
		{
			if (plr_distance(&all->plr, all->enem[l].pos_x, all->enem[l].pos_y, 0.8))
			{
				all->enem[l].action = 'd';
				all->enem[l].going = '2';
			}
		}
	}
}


void attack_enemy(t_plr *plr, t_enemy *en)
{
	if (en->action != 'a' && en->action != 'd')
	{
		if (en_distance(en, plr->pos_x, plr->pos_y, 0.5))
		{
			en->action = 'a';
			plr->hp--;
		}
	}
}

int	core(t_all *all)
{
	all->process_time = clock();

	time_t current_time;
	int	timer;
	int	fps;
	char *str;
	char *str2;

	// ### timer ### //
	current_time = clock();
	timer = (current_time - all->start_time) / CLOCKS_PER_SEC;
	// ### end_timer ### //

	if (timer % 2 == 0 && timer != all->oldtime)
	{
		printf("%d | plr_x = %f | plr_y = %f | dir_x = %d | dir_y = %d\n", timer, all->plr.pos_x, all->plr.pos_y, all->plr.dir_x, all->plr.dir_y);
		all->oldtime = timer;
	}
	if (!ft_strchr("wasd", all->plr.action))
		if (!movement(all))
			autostep(all);
	attack(all);
	int l = -1;
	while (++l < 4)
	{
		pathfind(all->map, &all->enem[l], all->plr.pos_x, all->plr.pos_y);
		move_enemy(l, all->enem, &all->plr);
		attack_enemy(&all->plr, &all->enem[l]);
	}
	steps(all->plr.pos_x, all->plr.pos_y, &all->steps, all->plr.action);
	take_coin(all);

	

	movecam(all);
	new_img(all);
	if (all->steps != all->laststeps)
	{
		//printf("COUNT_STEPS=%d\n", all->steps);
		all->laststeps = all->steps;
	}


	// ### FPS ### //
	current_time = clock();
	fps = CLOCKS_PER_SEC / (current_time - all->process_time);
	while (fps > MAX_FPS)
		fps = CLOCKS_PER_SEC / (clock() - all->process_time);
	str = ft_itoa(timer);
	str = ft_strjoin(str, " second left");
	mlx_string_put(all->win.mlx, all->win.win, 10, 20, 0xFFFFFF, str);
	str2 = ft_itoa(fps);
	str2 = ft_strjoin(str2, " fps");
	mlx_string_put(all->win.mlx, all->win.win, 10, 40, 0xFFFFFF, str2);
	free(str);
	free(str2);
	// ### end_FPS ### //

	return (0);
}
