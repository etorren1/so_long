#ifndef TEXTURIES_H
#define TEXTURIES_H

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

typedef struct s_alltex {
	t_tex       topwall;
	t_tex		sidewall;
    t_tex       exit;
    t_tex       *rwalk;
	t_tex       *lwalk;
	t_tex       *twalk;
	t_tex       *bwalk;
	t_tex		*dieban;
	t_tex		*rattack;
	t_tex		*lattack;
	t_tex		*tattack;
	t_tex		*battack;
    t_tex       sprite;
	t_tex       spear;
	t_tex       bspear;
	t_tex       *dead;
	t_tex		box;
}	t_alltex;

#endif