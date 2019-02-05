/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:28:26 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/05 17:54:47 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	update_ants(t_ant *ants_in_ways, t_list *path, t_ant ant)
{
	t_ant	prev;
	int		i;
	t_ant	temp;

	i = 0;
	path = path->next;
	while (path)
	{
		prev = DOBLE_DEREF(path)->ant;
		if (i == 0)
			DOBLE_DEREF(path)->ant = ant;
		if (prev.ant_id == NO_ANT)
			break ;
		if (prev.ant_id != NO_ANT && prev.way_id != NO_ANT)
			DOBLE_DEREF(path->next)->ant = prev;
		if (DOBLE_DEREF(path)->type == END)
		{
			i = 0;
			while (ants_in_ways[i].ant_id != NO_ANT)
				++i;
			ants_in_ways[i] = prev;
			break ;
		}
		path = path->next;
		++i;
	}
}

void	scatter_ants(t_lemin *lemin, t_list *paths)
{
	t_ant	ants_in_ways[lemin->ants_count];
	int		ant_id;
	t_ant	ant;
	int		i;

	ant_id = 0;
	ft_memset(ants_in_ways, NO_ANT, sizeof(t_ant) * lemin->ants_count);
	while (ants_in_ways[lemin->ants_count - 1].ant_id == NO_ANT)
	{
		i = 0;
		while (paths)
		{
			ant.ant_id = ant_id;
			ant.way_id = i;
			update_ants(ants_in_ways, *((t_list **)(paths->content)), ant);
			for (t_list *lol = *((t_list **)(paths->content)); lol; lol = lol->next)
			{
				ft_printf("%s, %lu, %lu ", DOBLE_DEREF(lol)->name, DOBLE_DEREF(lol)->ant.ant_id, DOBLE_DEREF(lol)->ant.way_id);
				if (!(lol->next))
					ft_printf("\n");
				else
					ft_printf(" ----> ");
			}
			paths = paths->next;
			++ant_id;
			++i;
		}
	}
}
