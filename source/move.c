#include "../includes/so_long.h"

int    blocked(t_all *all, char key, char *front_obj, char *back_obj)
{
    all->plr.dir_y = 0;
    all->plr.dir_x = 0;
    if (key == 'w')
        all->plr.dir_y = -1;
    if (key == 's')
        all->plr.dir_y = 1;
    if (key == 'a')
        all->plr.dir_x = -1;
    if (key == 'd')
        all->plr.dir_x = 1;
    if (all->map[(int)round(all->plr.pos_y + all->plr.dir_y)]\
         [(int)round(all->plr.pos_x + all->plr.dir_x)] == '1'
          || ((ft_strchr(front_obj, all->map[(int)round(all->plr.pos_y + all->plr.dir_y)]\
         [(int)round(all->plr.pos_x + all->plr.dir_x)]) || all->obj.action == '1')
          && ft_strchr(back_obj, all->map[(int)round(all->plr.pos_y + all->plr.dir_y * 2)]\
         [(int)round(all->plr.pos_x + all->plr.dir_x * 2)])))
        return (1);
    return (0);
}

int    movement(t_all *all)
{
    if (all->plr.action == 'd')
        return (0);
    if (all->key.w == '1' && all->plr.h_move != '1' && all->obj.action != '1'
         && !blocked(all, 'w', "1B", "1BCE"))
    {
        all->plr.pos_y -= SPEED;
        all->plr.action = 't';
        all->plr.v_move = '1';
    }
    else if (all->key.s == '1' && all->plr.h_move != '1' && all->obj.action != '1'
         && !blocked(all, 's', "1B", "1BCE"))
    {
        all->plr.pos_y += SPEED;
        all->plr.action = 'b';
        all->plr.v_move = '1';
    }
    else if (all->key.a == '1' && all->plr.v_move != '1' && all->obj.action != '1'
         && !blocked(all, 'a', "1B", "1BCE"))
    {
        all->plr.pos_x -= SPEED;
        all->plr.action = 'l';
        all->plr.h_move = '1';
    }
    else if (all->key.d == '1' && all->plr.v_move != '1' && all->obj.action != '1'
         && !blocked(all, 'd', "1B", "1BCE"))
    {
        all->plr.pos_x += SPEED;
        all->plr.action = 'r';
        all->plr.h_move = '1';
    }
    else
        return (0);
    return (1);
}
