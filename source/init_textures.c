
#include "../includes/so_long.h"

t_tex	new_texture(t_all *all, t_win *win, char *path)
{
	t_tex	tex;

	tex.img = mlx_xpm_file_to_image(win->mlx, path, &tex.width, &tex.height);
	if (tex.img == NULL)
		error(all, 3);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel,
			 &tex.line_length, &tex.endian);
	return (tex);
}

void	get_textures(t_all *all)
{
	all->tex.topwall = new_texture(all, &all->win, "./pics/topwalldarker.xpm");
	all->tex.sidewall = new_texture(all, &all->win, "./pics/sidewall.xpm");
	all->tex.exit = new_texture(all, &all->win, "./pics/exit.xpm");
	all->tex.lwalk[0] = new_texture(all, &all->win, "./pics/left-walk1.xpm");
	all->tex.lwalk[1] = new_texture(all, &all->win, "./pics/left-walk2.xpm");
	all->tex.lwalk[2] = new_texture(all, &all->win, "./pics/left-walk3.xpm");
	all->tex.lwalk[3] = new_texture(all, &all->win, "./pics/left-walk2.xpm");
	all->tex.rwalk[0] = new_texture(all, &all->win, "./pics/right-walk1.xpm");
	all->tex.rwalk[1] = new_texture(all, &all->win, "./pics/right-walk2.xpm");
	all->tex.rwalk[2] = new_texture(all, &all->win, "./pics/right-walk3.xpm");
	all->tex.rwalk[3] = new_texture(all, &all->win, "./pics/right-walk2.xpm");
	all->tex.twalk[0] = new_texture(all, &all->win, "./pics/top-walk1.xpm");
	all->tex.twalk[1] = new_texture(all, &all->win, "./pics/top-walk2.xpm");
	all->tex.twalk[2] = new_texture(all, &all->win, "./pics/top-walk3.xpm");
	all->tex.twalk[3] = new_texture(all, &all->win, "./pics/top-walk2.xpm");
	all->tex.bwalk[0] = new_texture(all, &all->win, "./pics/bot-walk1.xpm");
	all->tex.bwalk[1] = new_texture(all, &all->win, "./pics/bot-walk2.xpm");
	all->tex.bwalk[2] = new_texture(all, &all->win, "./pics/bot-walk3.xpm");
	all->tex.bwalk[3] = new_texture(all, &all->win, "./pics/bot-walk2.xpm");
	all->tex.dieban[0] = new_texture(all, &all->win, "./pics/banner_die1.xpm");
	all->tex.dieban[1] = new_texture(all, &all->win, "./pics/banner_die2.xpm");
	all->tex.dieban[2] = new_texture(all, &all->win, "./pics/banner_die3.xpm");
	all->tex.sprite = new_texture(all, &all->win, "./pics/coin.xpm");
	all->tex.box = new_texture(all, &all->win, "./pics/box.xpm");
	all->tex.spear = new_texture(all, &all->win, "./pics/hiddenspear.xpm");
	all->tex.bspear = new_texture(all, &all->win, "./pics/brokenspear.xpm");
	all->tex.dead[0] = new_texture(all, &all->win, "./pics/deadonspear1.xpm");
	all->tex.dead[1] = new_texture(all, &all->win, "./pics/deadonspear2.xpm");
	all->tex.dead[2] = new_texture(all, &all->win, "./pics/deadonspear3.xpm");
	all->tex.dead[3] = new_texture(all, &all->win, "./pics/deadonspear4.xpm");
	all->tex.dead[4] = new_texture(all, &all->win, "./pics/deadonspear5.xpm");
	all->tex.dead[5] = new_texture(all, &all->win, "./pics/deadonspear6.xpm");
	all->tex.dead[6] = new_texture(all, &all->win, "./pics/deadonspear7.xpm");
	all->tex.dead[7] = new_texture(all, &all->win, "./pics/deadonspear8.xpm");

	all->tex.lattack[0] = new_texture(all, &all->win, "./pics/left_attack_player_1.xpm");
	all->tex.lattack[1] = new_texture(all, &all->win, "./pics/left_attack_player_2.xpm");
	all->tex.lattack[2] = new_texture(all, &all->win, "./pics/left_attack_player_3.xpm");
	all->tex.lattack[3] = new_texture(all, &all->win, "./pics/left_attack_player_4.xpm");
	all->tex.rattack[0] = new_texture(all, &all->win, "./pics/right_attack_player_1.xpm");
	all->tex.rattack[1] = new_texture(all, &all->win, "./pics/right_attack_player_2.xpm");
	all->tex.rattack[2] = new_texture(all, &all->win, "./pics/right_attack_player_3.xpm");
	all->tex.rattack[3] = new_texture(all, &all->win, "./pics/right_attack_player_4.xpm");
	all->tex.tattack[0] = new_texture(all, &all->win, "./pics/top_attack_player_1.xpm");
	all->tex.tattack[1] = new_texture(all, &all->win, "./pics/top_attack_player_2.xpm");
	all->tex.tattack[2] = new_texture(all, &all->win, "./pics/top_attack_player_3.xpm");
	all->tex.tattack[3] = new_texture(all, &all->win, "./pics/top_attack_player_4.xpm");
	all->tex.battack[0] = new_texture(all, &all->win, "./pics/bot_attack_player_1.xpm");
	all->tex.battack[1] = new_texture(all, &all->win, "./pics/bot_attack_player_2.xpm");
	all->tex.battack[2] = new_texture(all, &all->win, "./pics/bot_attack_player_3.xpm");
	all->tex.battack[3] = new_texture(all, &all->win, "./pics/bot_attack_player_4.xpm");
}
