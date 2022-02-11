
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
# include "texturies.h"
# include "objects.h"
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

typedef struct s_key {
	char		w;
	char		a;
	char		s;
	char		d;
	char		f;
	char		sp;
}		t_key;

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
int	key_press(int key, t_all *all);
int	key_unpress(int key, t_all *all);
void			fill_background(t_all *all);
void			map_print(t_all *all);
void			parser(char *argv, t_all *all);
void	        draw_back(t_all *all);
void        	error(t_all *all, int err_id);
void	        get_textures(t_all *all);
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
void	get_resolution(t_all *all, t_list **lst);
int	empty_string(char *line);
void	check_map(t_all *all, int size, int exit, int collect);
void	put_scale_without_indent(t_all *all, int ybegin, int xbegin, int color);
//void	my_get_screen_size(int *width, int *height);

#endif
