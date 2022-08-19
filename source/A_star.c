#include "../includes/so_long.h"

// typedef struct s_pos
// {
//     int x;
//     int y;
//     int weight;
// } t_pos;

void    printcont(void *pos)
{
    t_pos *cont = (t_pos*)pos;
    printf(">> x = %d | y = %d | w= %d\n", cont->x, cont->y, cont->weight);
}

static int     ft_heurestic(t_pos *a, t_pos *b)
{
    return(abs(a->x - b->x) + abs(a->y - b->y));
}

t_node* ft_nodefind(t_node *node, void *content)
{
    while (node)
    {
        if (node->content == content) { printf("Find it!\n");
            return (node); }
        node = node->next;
    }
    return (0);
}

int     not_in(t_node *node, t_pos *pos)
{
    t_pos *cont;

    while (node)
    {
        cont = (t_pos*)node->content;
        if (cont->x == pos->x && cont->y == pos->y)
            return (0);
        node = node->next;
    }
    return (1);
}

int     not_wall(char **map, t_pos *pos)
{
    if (map[pos->y][pos->x] == '1' || map[pos->y][pos->x] == 'B')
        return (0);
    return (1);
}

void	ft_nodedel_same(t_node **node, t_pos *content)
{
	t_node  *tmp_prev;
    t_node  *tmp_after;
    t_node  *tmp;
    t_node  *head;

    tmp = *node;
    head = tmp;
    while (tmp)
    {
        if (((t_pos*)tmp->content)->x == content->x && ((t_pos*)tmp->content)->y == content->y)
        {
            if (!tmp->next && !tmp->prev)
            {
                free(tmp);
                *node = NULL;
                break;
            }
            else
            {
                tmp_prev = tmp->prev;
                tmp_after = tmp->next;
                if (tmp_after)
                {
                    tmp_after->prev = tmp_prev;
                    *node = tmp_after;
                }
                if (tmp_prev)
                {
                    tmp_prev->next = tmp_after;
                    *node = head;
                }
                free(tmp);
                break ; 
            }
        }
        tmp = tmp->next;
    }
}


void    addneighbour(t_node **open, t_node *close, t_pos *curr, t_pos *end, char **map, int a, int b)
{
    t_pos *now;

    now = malloc(sizeof(t_pos));
    now->x = curr->x + a;
    now->y = curr->y + b;
    now->weight = 1 + ft_heurestic(curr, end);
    if (not_in(*open, now) && not_in(close, now) && not_wall(map, now))
        ft_nodeadd_back(open, ft_nodenew(now));
    else
        free(now);
}

t_pos   *lowest_weight(t_node *openSet)
{
    t_node *tmp;
    t_pos *winner;
    t_pos *now;
    
    tmp = openSet;
    if (tmp)
    {
        winner = malloc(sizeof(t_pos));
        winner->weight = ((t_pos*)tmp->content)->weight;
        winner->x = ((t_pos*)tmp->content)->x;
        winner->y = ((t_pos*)tmp->content)->y;
    }
    // Find shortest point
    while (tmp)
    {
        now = tmp->content;
        if (now->weight < winner->weight)
        {
            winner->weight = now->weight;
            winner->x = now->x;
            winner->y = now->y;
        }
        tmp = tmp->next;
    }
    return(winner);
} 

int     is_neighbour(t_pos *a, t_pos *b)
{
    if ((abs(a->x - b->x) + abs(a->y - b->y)) == 1)
        return (1);
    return (0);
}

t_node    *get_final_way(t_node *closeSet)
{
    t_node *rev;
    t_node *way;
    t_pos *end;

    rev = ft_nodelast(closeSet);
    end = rev->content; 
    way = ft_nodenew(end);
    rev = rev->prev;
    while (rev)
    {
        if (is_neighbour(end, rev->content))
        {
            ft_nodeadd_front(&way, ft_nodenew(rev->content));
            end = rev->content;
        }
        else
            free(rev->content);
        rev = rev->prev;
    }
    return (way);
}

void    f_void(void *content)
{
    (void)content;
}

// int     ftoi(float val)
// {
//     if (val - (int)val > 0.5)
//          return((int)ceilf(val));
//     else
//          return((int)floorf(val));
// }

// static int     distance(t_enemy *en, float x_end, float y_end, int weight)
// {
//     if (x_end < en->pos_x || en->pos_y > y_end)
//     {
//         if (weight > 0)
//             return (1); 
//     }
//     else if (weight > 1)
//         return (1);
//     return (0);
// }

t_node    *pathfind(char **map, t_enemy *en, float x_end, float y_end)
{
    t_pos *end;
    t_pos *current;
    t_node *openSet;
    t_node *closeSet;

    current = malloc(sizeof(t_pos));
    end = malloc(sizeof(t_pos));
    end->x = (int)x_end;
    end->y = (int)y_end;
    current->x = (int)en->pos_x;
    current->y = (int)en->pos_y;
    current->weight = ft_heurestic(current, end);
    if (map[end->y][end->x] != '1' && map[end->y][end->x] != 'B'  && current->weight < 25)
    // && distance(en, x_end, y_end, current->weight))
    {
        openSet = ft_nodenew(current);
        closeSet = NULL;
        while (ft_nodesize(openSet) > 0 && ft_nodesize(closeSet) < 150)
        {
            ft_nodedel_same(&openSet, current);
            ft_nodeadd_back(&closeSet, ft_nodenew(current));
            addneighbour(&openSet, closeSet, current, end, map, 1, 0);
            addneighbour(&openSet, closeSet, current, end, map, -1, 0);
            addneighbour(&openSet, closeSet, current, end, map, 0, 1);
            addneighbour(&openSet, closeSet, current, end, map, 0, -1);   
            current = lowest_weight(openSet);
            // printf("\e[31mcurrent pos>> x = %d| y = %d | w = %d\e[0m\n", current->x, current->y, current->weight);
            if (current->x == end->x && current->y == end->y)
            {
                ft_nodeadd_back(&closeSet, ft_nodenew(current));
                en->way = get_final_way(closeSet);
                ft_nodeclear(&closeSet, f_void);
                // printf("Done!\n");
                break;
            }
        }
        if (!openSet || ft_nodesize(closeSet) >= 150)
            en->way = NULL;
        ft_nodeclear(&openSet, free);
        return (en->way);
    }
    en->way = NULL;
    return (en->way);
}
