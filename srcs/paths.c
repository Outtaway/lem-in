/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:34:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/04 13:54:54 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	bfs(t_lemin *lemin)
{
	t_list		*queue;
	t_list		*iter;
	t_farm		*conn;
	t_list		*node;

	lemin->start->state = MARKED;
	queue = NULL;
	ft_lstadd(&queue, ft_lstnew(&(lemin->start), sizeof(lemin->start)));
	while (queue != NULL)
	{
		node = queue_pop(&queue);
		iter = DOBLE_DEREF(node)->connections;
		while (iter)
		{
			conn = DOBLE_DEREF(iter);
			if (conn->state == UNMARKED)
			{
				conn->state = MARKED;
				conn->distance = DOBLE_DEREF(node)->distance + 1;
				ft_lstadd(&queue, ft_lstnew(&conn, sizeof(conn)));
			}
			iter = iter->next;
		}
		CLEAR_NODE(node);
	}
}

void		recursive_path(t_farm *farm, t_list **path)
{
	t_list	*conn;
	t_farm	*to_next;
	int		min;

	ft_lstadd(path, ft_lstnew(&farm, sizeof(farm)));
	if (farm->type == START)
		return ;
	farm->is_blocked = BLOCKED;
	conn = farm->connections;
	to_next = NULL;
	min = _INT_MAX;
	while(conn)
	{
		if (DOBLE_DEREF(conn)->distance < min &&
				DOBLE_DEREF(conn)->is_blocked != BLOCKED)
		{
			to_next = DOBLE_DEREF(conn);
			min = to_next->distance;
		}
		conn = conn->next;
	}
	if (to_next)
		recursive_path(to_next, path);
}

void	shortest_paths(t_lemin *lemin, t_list **paths)
{
	t_list		*path;
	t_list		*conn;

	conn = lemin->end->connections;
	lemin->end->is_blocked = BLOCKED;
	while (conn)
	{
		path = NULL;
		ft_lstadd(&path, ft_lstnew(&(lemin->end), sizeof(lemin->end)));
		recursive_path(DOBLE_DEREF(conn), &path);
		ft_lstadd(paths, ft_lstnew(&path, sizeof(path)));
		conn = conn->next;
	}
}

void	display_paths(t_list *paths)
{
	t_list		*path;

	while (paths)
	{
		path = *((t_list **)(paths->content));
		while (path)
		{
			ft_printf(path->next ? "%s -> " : "%s\n" , DOBLE_DEREF(path)->name);
			path = path->next;
		}
		paths = paths->next;
	}
}
