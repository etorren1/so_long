#ifndef OBJECTS_H
#define OBJECTS_H

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
    int         hp;
	char		action;
	char		h_move;
	char		v_move;
	char		last_dir;
}               t_plr;

typedef struct s_enemy {
	float		pos_x;
	float		pos_y;
    float       atime;
	int			dir_x;
	int			dir_y;
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

#endif