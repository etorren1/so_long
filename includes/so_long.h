
#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "pthread.h"
# define SCALE  60
# define SPEED 0.05
# define MAX_FPS 60

typedef struct s_win {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			w;
	int			h;
	int			ind_w;
	int			ind_h;
}				t_win;

typedef struct s_tex {
	int			width;
	int			height;
	float		pos_x;
	float		pos_y;
	float		step;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_tex;

typedef struct s_pos
{
    int x;
    int y;
    int weight;
} t_pos;

typedef struct s_plr {
    float       pos_x;
    float       pos_y;
	float		dtime;
	float		atime;
	int			dir_x;
	int			dir_y;
	char		action;
	char		h_move;
	char		v_move;
	char		last_dir;
}               t_plr;

typedef struct s_enemy {
	float		pos_x;
	float		pos_y;
	int			old_x;
	int			old_y;
	t_pos		*pos1;
	t_pos		*pos2;
	t_node 		*way;
	int			steps;
	char		dir;
	char		going;
	char		action;
	t_tex		*laststep;
}				t_enemy;

typedef struct s_obj {
	float		pos_x;
	float		pos_y;
	char		type;
	char		action;
	char		oldplraction;
}		t_obj;

typedef struct s_static_obj {
	int			pos_x;
	int			pos_y;
	char		type;
	char		status;
}		t_static_obj;

typedef struct s_key {
	char		w;
	char		a;
	char		s;
	char		d;
	char		f;
	char		sp;
}		t_key;

typedef struct s_alltex {
	t_tex       topwall;
	t_tex		sidewall;
    t_tex       exit;
    t_tex       *rwalk;
	t_tex       *lwalk;
	t_tex       *twalk;
	t_tex       *bwalk;
	t_tex		*dieban;
    t_tex       sprite;
	t_tex       spear;
	t_tex       bspear;
	t_tex       *dead;
	t_tex		box;
}	t_alltex;

typedef struct s_all {
	t_win		win;
    t_plr       plr;
	t_key		key;
	t_alltex	tex;
	t_obj		obj;
	
	t_static_obj	*spears;
	int			spears_count;
	time_t		start_time;
	time_t		process_time;
    char        **map;
	int			map_size_x;
	int			map_size_y;
	int			steps;
	int			score;
	int			laststeps;

	//tmp
	t_enemy		enem[4];
	int			oldtime;
}				t_all;


void	steps(float x, float y, int *steps, char action);
int	round100(float	pos);
void	my_get_screen_size(int *width, int *height);
int	key_press(int key, t_all *all);
int	key_unpress(int key, t_all *all);
void			fill_background(t_all *all);
void			map_print(t_all *all);
void			parser(char *argv, t_all *all);
void	        draw_back(t_all *all);
void        	error(t_all *all, int err_id);
void	        get_texturies(t_all *all);
void			new_img(t_all *all);
int   			core(t_all *all);
int    movement(t_all *all);
int check_pos(char **map, float pos_y, float pos_x, char ch);
void			clean_exit(t_all *all, int id);
int				my_mlx_pixel_get(t_tex *tex, char *addr, int x, int y);
void			my_mlx_pixel_put(t_win *win, int x, int y, int color);
void			draw_texture(t_win *win, t_tex *tex, int x, int y);
void			put_scale(t_all *all, int ybegin, int xbegin, int color);
void	put_texture(t_all *all, t_tex *tex, float ybegin, float xbegin);

#endif
