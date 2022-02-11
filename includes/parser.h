
#ifndef PARSER_H
# define PARSER_H

# include "so_long.h"

int		cases(int i, int j, char **map, int size);
void	check_map(t_all *all, int size, int exit, int collect);
void	get_resolution(t_all *all, t_list **lst);
int		empty_string(char *line);

#endif
