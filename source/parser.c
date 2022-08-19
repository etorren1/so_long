
#include "../includes/so_long.h"

void	inite_params(t_all *all)
{
	//tmp
	int l = -1;
	while (++l < 4)
	{
		all->enem[l].action = 'n';
		all->enem[l].going = '0';
	}


	all->spears_count = 0;
	all->steps = 0;
	all->map = NULL;
	all->plr.action = 'n';
	all->plr.h_move = '0';
	all->plr.v_move = '0';
	all->obj.action = '0';
	all->plr.dtime = 0.0;
	all->plr.atime = 0.0;
	all->obj.pos_y = 0.0;
	all->obj.pos_x = 0.0;
	all->win.ind_h = 0;
	all->win.ind_w = 0;
	all->plr.dir_y = 1;
	all->plr.dir_x = 0;
	all->plr.hp = 5;
	all->score = 0;
	all->tex.lwalk = malloc(sizeof(t_tex) * 4);
	all->tex.rwalk = malloc(sizeof(t_tex) * 4);
	all->tex.twalk = malloc(sizeof(t_tex) * 4);
	all->tex.bwalk = malloc(sizeof(t_tex) * 4);
	all->tex.lattack = malloc(sizeof(t_tex) * 4);
	all->tex.rattack = malloc(sizeof(t_tex) * 4);
	all->tex.tattack = malloc(sizeof(t_tex) * 4);
	all->tex.battack = malloc(sizeof(t_tex) * 4);
	all->tex.dieban = malloc(sizeof(t_tex) * 3);
	all->tex.dead = malloc(sizeof(t_tex) * 8);
}

void	make_map(t_all *all, t_list **lst, int size)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = *lst;
	all->map = ft_calloc(size + 1, sizeof(char *));
	while (temp)
	{
		all->map[i++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	all->map[i] = NULL;
	check_map(&*all, size - 1, 0, 0);
}

void	read_map(t_all *all, char *argv)
{
	int		fd;
	t_list	*lst;
	char	*line;

	lst = NULL;
	fd = open(argv, O_RDWR);
	if (fd < 0)
		error(all, 5);
	while (get_next_line(fd, &line))
	{
		if (!empty_string(line))
			ft_lstadd_back(&lst, ft_lstnew(line));
	}
	if (!empty_string(line))
		ft_lstadd_back(&lst, ft_lstnew(line));
	close(fd);
	make_map(all, &lst, ft_lstsize(lst));
	get_resolution(all, &lst);
	ft_lstclear(&lst, free);
}

static void	get_spawn_point(t_all *all, t_plr *plr)
{
	int	i;
	int	j;
	int k = 0;
	int	check;

	j = -1;
	check = 0;
	while (all->map[++j])
	{
		i = 0;
		while (all->map[j][i])
		{
			if (ft_strchr("P", all->map[j][i]))
			{
				plr->pos_x = i;
				plr->pos_y = j;
				check++;
			}
			if (ft_strchr("e", all->map[j][i]))
			{
				all->enem[k].pos_x = i;
				all->enem[k].pos_y = j;
				k++;
			}
			i++;
		}
	}
	if (check != 1)
		error(all, 1);
}

void	get_obj_count(t_all *all)
{
	int	i;
	int	j;
	int	obj;

	j = -1;
	obj = 0;
	while (all->map[++j])
	{
		i = -1;
		while (all->map[j][++i])
		{
			if (ft_strchr("S", all->map[j][i]))
				all->spears_count++;
		}
	}
	all->spears = malloc(sizeof(t_static_obj) *  all->spears_count);
}

void	get_obj_value(t_all *all)
{
	int	i;
	int	j;
	int	k;

	j = -1;
	k = -1;
	while (all->map[++j])
	{
		i = -1;
		while (all->map[j][++i])
		{
			if (ft_strchr("S", all->map[j][i]))
			{
				all->spears[++k].pos_x = i;
				all->spears[k].pos_y = j;
				all->spears[k].status = 'n';
			}
		}
	}
}

void	parser(char *argv, t_all *all)
{
	inite_params(all);
	read_map(all, argv);
	get_spawn_point(all, &all->plr);
	get_obj_count(all);
	get_obj_value(all);
}
