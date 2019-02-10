/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/09 22:45:32 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	display_input(t_list *input)
{
	if (input)
	{
		display_input(input->next);
		write(1, *((char **)(input->content)),
				ft_strlen(*((char **)(input->content))));
		write(1, "\n", 1);
	}
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

int		main(int argc, char **argv)
{
	t_lemin		lemin;
	t_list		*paths;
	char		*line;

	ft_bzero(&lemin, sizeof(lemin));
	paths = NULL;
	get_lemin_struct(&lemin);
	if (!lemin.start || !lemin.end)
		ERROR(6);
	if (!lemin.start->connections || !lemin.end->connections)
		ERROR(40);
	bfs(&lemin);
	if (lemin.end->distance == _INT_MAX)
		ERROR(7);
	shortest_paths(&lemin, &paths);
	if (!paths)
		ERROR(50);
	display_input(lemin.input);
	// display_paths(paths);
	scatter_ants(&lemin, paths);
	return (0);
}
