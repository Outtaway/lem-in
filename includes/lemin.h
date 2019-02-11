/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:17:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/11 18:49:58 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../gnl/get_next_line.h"

# define WR(fd, line) write(fd, line, ft_strlen(line))
# define ERROR(code) { WR(2, "ERROR\n"); exit(code); }
# define DEREF(list) ((t_farm *)((list)->content))
# define DOBLE_DEREF(list) (*((t_farm **)(list->content)))
# define CLEAR_NODE(node) free(node->content); free(node);
# define SWAP(t, left, r) { t temp; temp = left; left = r; r = temp; }
# define TEMP_VAR(type, value) type temp = value;

# define REGULAR 0
# define START 1
# define END 2
# define BUFF 32

# define UNMARKED 0
# define MARKED 1

# define BLOCKED 1
# define UNBLOCKED 0
# define NO_ANT -1

# pragma pack(1)

typedef struct				s_ant
{
	int						ant_id;
	int						way_id;
}							t_ant;

typedef struct				s_farm
{
	unsigned char			type : 2;
	unsigned char			state : 2;
	unsigned char			is_blocked : 1;
	int						x;
	int						y;
	int						ants_count;
	int						distance;
	char					name[BUFF];
	t_list					*connections;
	t_ant					ant;
}							t_farm;

typedef struct				s_parser
{
	unsigned char			rooms : 1;
	unsigned char			ants : 1;
	unsigned char			conn : 1;
}							t_parser;

typedef struct				s_lemin
{
	t_list					*farms;
	t_farm					*start;
	t_farm					*end;
	t_list					*input;
	int						ants_count;
	t_parser				parser;
}							t_lemin;

void						start_end(t_lemin *lemin);
t_list						*get_node_by_type(t_list *list, char type);
void						scatter_ants(t_lemin *lemin, t_list *paths);
t_list						*get_node_by_name(t_list *list, char *name);
void						clear_paths(t_list *paths);
int							list_size(t_list *list);
char						farm_exists(t_farm *farm, t_list *farms);
char						line_farm(char *line);
char						line_ants(char *line);
char						line_connection(char *line);
void						shortest_paths(t_lemin *lemin, t_list **paths);
void						bfs(t_lemin *lemin);
void						get_lemin_struct(t_lemin *lemin, t_parser *parser);
t_list						*queue_pop(t_list **list);

#endif
