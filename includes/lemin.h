/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:17:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/02 18:23:35 by kpshenyc         ###   ########.fr       */
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

# define REGULAR 0
# define START 1
# define END 2
# define BUFF 64

# define UNMARKED 0
# define MARKED 1
# define DONE 2

# define BLOCKED 1
# define UNBLOCKED 0

typedef struct				s_farm
{
		char				name[BUFF];
		t_list				*connections;
		int					x;
		int					y;
		unsigned char		type : 2;
		unsigned char		state : 2;
		int					distance;
		unsigned char		is_blocked : 2;
}							t_farm;

typedef struct				s_lemin
{
		t_list				*farms;
		t_farm				*start;
		t_farm				*end;
		size_t				farms_count;
		size_t				ants_count;
		size_t				ant;
}							t_lemin;

void						shortest_path(t_lemin *lemin);
void						bfs(t_lemin *lemin);
void						get_lemin_struct(t_lemin *lemin);
void						algorithm(t_lemin *lemin);
t_list						*queue_pop(t_list **list);

#endif

