/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:34:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/02 18:18:33 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	bfs(t_lemin *lemin)
{
	t_list		*queue;
	t_farm		*obj;
	t_list		*iter;
	t_farm		*conn;
	t_list		*node;

	lemin->start->state = MARKED;
	queue = NULL;
	ft_lstadd(&queue, ft_lstnew(&(lemin->start), sizeof(lemin->start)));
	while (queue != NULL)
	{
		node = queue_pop(&queue);
		obj = DOBLE_DEREF(node);
		iter = obj->connections;
		while (iter)
		{
			conn = DOBLE_DEREF(iter);
			if (conn->state == UNMARKED)
			{
				conn->state = MARKED;
				conn->distance = obj->distance + 1;
				ft_lstadd(&queue, ft_lstnew(&conn, sizeof(conn)));
			}
			iter = iter->next;
		}
		free(node->content);
		free(node);
	}
}

void		recursive_path(t_farm *farm, t_list **path)
{
	t_list	*conn;
	int 	min;
	t_farm	*to_next;

	ft_lstadd(path, ft_lstnew(&farm, sizeof(farm)));
	if (farm->type == START)
		return ;
	farm->is_blocked = (farm->type != END) ? BLOCKED : UNBLOCKED;
	conn = farm->connections;
	to_next = DOBLE_DEREF(conn);
	min = to_next->distance;
	conn = conn->next;
	while(conn)
	{
		if (DOBLE_DEREF(conn)->distance < min)
		{
			to_next = DOBLE_DEREF(conn);
			min = to_next->distance;
		}
		conn = conn->next;
	}
	recursive_path(to_next, path);
}

void	shortest_path(t_lemin *lemin)
{
	t_list		*path;

	path = NULL;
	recursive_path(lemin->end, &path);
	while (path)
	{
		ft_printf(path->next ? "%s -> " : "%s\n" , DOBLE_DEREF(path)->name);
		path = path->next;
	}
}
