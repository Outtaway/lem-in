/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/12 15:10:21 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		display_input(t_list *input)
{
	if (input)
	{
		display_input(input->next);
		write(1, *((char **)(input->content)),
				ft_strlen(*((char **)(input->content))));
		write(1, "\n", 1);
	}
	return (0);
}

int		list_size(t_list *list)
{
	int		len;

	len = 0;
	while (list)
	{
		list = list->next;
		++len;
	}
	return (len);
}

t_list	*queue_pop(t_list **list)
{
	t_list	*res;
	t_list	*iter;

	if ((*list)->next)
	{
		iter = (*list);
		while (iter->next->next)
			iter = iter->next;
		res = iter->next;
		iter->next = NULL;
	}
	else
	{
		res = (*list);
		(*list) = NULL;
	}
	return (res);
}

void	clear_paths(t_list *paths)
{
	t_list *path;

	while (paths)
	{
		path = *((t_list **)(paths->content));
		while (path)
		{
			DOBLE_DEREF(path)->ant.way_id = NO_ANT;
			DOBLE_DEREF(path)->ant.ant_id = NO_ANT;
			path = path->next;
		}
		paths = paths->next;
	}
}

int		main(int argc, char **argv)
{
	t_lemin		lemin;
	t_list		*paths;

	ft_bzero(&lemin, sizeof(lemin));
	paths = NULL;
	get_lemin_struct(&lemin, &(lemin.parser));
	if (!lemin.start || !lemin.end || lemin.ants_count == 0)
		ERROR(6);
	if (!lemin.start->connections || !lemin.end->connections)
		ERROR(40);
	bfs(&lemin);
	if (lemin.end->distance == _INT_MAX)
		ERROR(7);
	shortest_paths(&lemin, &paths);
	if (!paths)
		ERROR(50);
	(argc > 1 && !ft_strcmp(argv[1], "--no_input"))
		? 0 : display_input(lemin.input);
	if (get_node_by_type(lemin.start->connections, END))
		start_end(&lemin);
	else
		scatter_ants(&lemin, paths);
	return (0);
}
