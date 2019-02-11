/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:34:21 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/11 18:48:44 by kpshenyc         ###   ########.fr       */
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
			if (conn->state == UNMARKED && conn->is_blocked == UNBLOCKED)
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

void	clear_graph(t_farm *start)
{
	t_list		*conn;

	if (start->is_blocked != BLOCKED)
		start->state = UNMARKED;
	conn = start->connections;
	while (conn)
	{
		if (DOBLE_DEREF(conn)->state == MARKED
		&& DOBLE_DEREF(conn)->is_blocked != BLOCKED)
			clear_graph(DOBLE_DEREF(conn));
		conn = conn->next;
	}
}

void	recursive_path(t_farm *farm, t_list **path)
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
	while (conn)
	{
		if (DOBLE_DEREF(conn)->distance < min &&
				DOBLE_DEREF(conn)->is_blocked == UNBLOCKED)
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
	while (conn)
	{
		path = NULL;
		lemin->end->is_blocked = BLOCKED;
		recursive_path(lemin->end, &path);
		if (DOBLE_DEREF(path)->type != START)
		{
			while (path)
			{
				TEMP_VAR(t_list *, path);
				path = path->next;
				free(temp->content);
				free(temp);
			}
		}
		else
			ft_lstadd(paths, ft_lstnew(&path, sizeof(path)));
		clear_graph(lemin->start);
		bfs(lemin);
		conn = conn->next;
	}
}

t_list	*get_node_by_type(t_list *list, char type)
{
	while (list)
	{
		if (DOBLE_DEREF(list)->type == type)
			return (list);
		list = list->next;
	}
	return (NULL);
}
