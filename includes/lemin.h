/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:17:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/05 17:56:08 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../gnl/get_next_line.h"

# define WR(line) write(1, line, ft_strlen(line))
# define ERROR() { WR("ERROR\n"); exit(1); }
# define DEL_GET(line) ft_strdel(&line); get_next_line(0, &line);
# define DEREF(list) ((t_farm *)((list)->content))
# define DOBLE_DEREF(list) (*((t_farm **)(list->content)))
# define CLEAR_NODE(node) free(node->content); free(node);
# define ADD_LINE(dst, str) ft_strcat(dst, str); ft_strcat(dst, "\n");

# define REGULAR 0
# define START 1
# define END 2
# define BUFF 64

# define UNMARKED 0
# define MARKED 1
# define DONE 2

# define BLOCKED 1
# define UNBLOCKED 0
# define NO_ANT -1

typedef struct				s_ant
{
	int						ant_id;
	int						way_id;
}							t_ant;

typedef struct				s_farm
{
		char				name[BUFF];
		t_list				*connections;
		int					x;
		int					y;
		unsigned char		type : 2;
		unsigned char		state : 2;
		int					distance;
		unsigned char		is_blocked : 1;
		t_ant				ant;
		int					ants_count;
}							t_farm;

typedef struct				s_lemin
{
		t_list				*farms;
		t_farm				*start;
		t_farm				*end;
		int					ants_count;
}							t_lemin;



void						scatter_ants(t_lemin *lemin, t_list *paths);
t_list						*get_node_by_name(t_list *list, char *name);

size_t						list_size(t_list *list);

char						line_connection(char *line);
char						line_numeric(char *line, char two_blanks);
void						get_paths_length(t_list **paths_length, t_list *paths);
void						display_paths(t_list *paths);
void						shortest_paths(t_lemin *lemin, t_list **paths);
void						bfs(t_lemin *lemin);
void						get_lemin_struct(t_lemin *lemin, char *input);
void						algorithm(t_lemin *lemin);
t_list						*queue_pop(t_list **list);

#endif

