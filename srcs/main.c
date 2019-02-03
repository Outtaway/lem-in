/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/03 17:35:52 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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

int		main(int argc, char **argv)
{
	t_lemin		lemin;
	t_list		*paths;
	t_list		*path;

	paths = NULL;
	ft_bzero(&lemin, sizeof(t_lemin));
	get_lemin_struct(&lemin);
	if (!lemin.start || !lemin.end)
		ERROR();
	bfs(&lemin);
	if (lemin.end->distance == _INT_MAX)
		ERROR();
	shortest_path(&lemin, &paths);
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
//	system("leaks lem-in");
	return (0);
}
