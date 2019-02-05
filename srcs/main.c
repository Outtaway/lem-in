/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/05 16:33:25 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t	list_size(t_list *list)
{
	size_t		len;

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
	char		*input;

	input = (char *)malloc(sizeof(char) * 1000000);
	get_lemin_struct(&lemin, input);
	if (!lemin.start || !lemin.end)
		ERROR();
	bfs(&lemin);
	if (lemin.end->distance == _INT_MAX)
		ERROR();
	shortest_paths(&lemin, &paths);
	display_paths(paths);
//	write(1, input, ft_strlen(input));
	scatter_ants(&lemin, paths);
	// system("leaks lem-in");
	free(input);
	return (0);
}
