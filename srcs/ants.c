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
	prev = DOBLE_DEREF(path)->ant;
	while (path)
	{
		if (i == 0)
			DOBLE_DEREF(path)->ant = ant;
		if (prev.ant_id == NO_ANT)
			break ;
		if (prev.ant_id != NO_ANT && prev.way_id != NO_ANT && DOBLE_DEREF(path)->type != END)
		{
			temp = DOBLE_DEREF(path->next)->ant;
			DOBLE_DEREF(path->next)->ant = prev;
			prev = temp;
		}
		else if (DOBLE_DEREF(path)->type == END)
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

int		*ants_in_each_way(t_ant *ants_in_ways, t_lemin *lemin, t_list *paths)
{
	int		*res;
	int		i;
	int		ants;
	int		j;

	res = (int *)malloc(sizeof(int) * list_size(paths));
	i = -1;
	while (++i < list_size(paths))
	{
		ants = 0;
		j = -1;
		while (++j < lemin->ants_count)
			if (ants_in_ways[j].way_id == i)
				ants++;
		res[i] = ants;
	}
	return (res);
}=

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

void	display_status(t_list *paths)
{
	t_list *path;

	while (paths)
	{
		path = (*((t_list **)(paths->content)))->next;
		while (path)
		{
			if (DOBLE_DEREF(path)->ant.ant_id != NO_ANT)
				ft_printf("L%d-%s ", DOBLE_DEREF(path)->ant.ant_id, DOBLE_DEREF(path)->name);
			path = path->next;
		}
		paths = paths->next;
	}
	write(1, "\n", 1);
}

void	move_ants(char new_ant, t_list *path, t_ant ant)
{

}

void	display_movements(t_lemin *lemin, t_ant *ants_in_ways, t_list *paths)
{
	int		*amounts_of_ants;
	int 	i;
	t_list	*temp;
	int		ant_id;

	ant_id = 1;
	amounts_of_ants = ants_in_each_way(ants_in_ways, lemin, paths);
	clear_paths(paths);
	while (lemin->end->ants_count != lemin->ants_count)
	{
		i = -1;
		temp = paths;
		while (++i < list_size(paths))
		{
			if (amounts_of_ants[i] > 0)
			{
				move_ants(1, *((t_list **)(temp->content)), (t_ant){.ant_id = ant_id, .way_id = i});
				--(amounts_of_ants[i]);
				ant_id++;
			}
			else
				move_ants(0, *((t_list **)(temp->content)), (t_ant){.ant_id = NO_ANT, .way_id = NO_ANT});
			temp = temp->next;
		}
		display_status(paths);
	}
	free(amounts_of_ants);
}

void	scatter_ants(t_lemin *lemin, t_list *paths)
{
	t_ant	*ants_in_ways;
	int		ant_id;
	t_ant	ant;
	int		i;
	t_list	*temp;

	ant_id = 0;
	ants_in_ways = (t_ant *)malloc(sizeof(t_ant) * lemin->ants_count);
	ft_memset(ants_in_ways, NO_ANT, sizeof(t_ant) * lemin->ants_count);
	while (ants_in_ways[lemin->ants_count - 1].ant_id == NO_ANT)
	{
		i = 0;
		temp = paths;
		while (paths)
		{
			ant.ant_id = ant_id;
			ant.way_id = i;
			update_ants(ants_in_ways, *((t_list **)(paths->content)), ant);
//			for (t_list *lol = *((t_list **)(paths->content)); lol; lol = lol->next)
//			{
//				ft_printf("name: %s, id: %lu, way: %lu ", DOBLE_DEREF(lol)->name, DOBLE_DEREF(lol)->ant.ant_id, DOBLE_DEREF(lol)->ant.way_id);
//				if (!(lol->next))
//					ft_printf("\n");
//				else
//					ft_printf(" ----> ");
//			}
			paths = paths->next;
			++ant_id;
			++i;
		}
		paths = temp;
	}
	display_movements(lemin, ants_in_ways, paths);
	free(ants_in_ways);
}


