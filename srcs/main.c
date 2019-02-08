/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/08 21:19:03 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	replace_by_null(char *c)
{

	*c = (*c == '\n') ? '\0' : *c;
}

void	replace_by_slash(char *c)
{
	*c = (*c == '\0')
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
	char		*input;
	char		*line;
	int			lol;

	input = (char *)malloc(sizeof(char) * 1000000);
	lol = read(0, input, 1000000);
	input[lol] = '\0';
	ft_striter(input, &replace_by_null);
	get_lemin_struct(&lemin, input);
	// if (!lemin.start || !lemin.end)
	// 	ERROR();
	// bfs(&lemin);
	// if (lemin.end->distance == _INT_MAX)
	// 	ERROR();
	// shortest_paths(&lemin, &paths);
	ft_striter(input, &replace_by_null);
	write(1, input, ft_strlen(input));
	// display_paths(paths);
//	scatter_ants(&lemin, paths);
	free(input);
	return (0);
}
