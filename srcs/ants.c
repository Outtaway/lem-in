/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: konstantin <konstantin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:28:26 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/09 22:16:47 by konstantin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	update_ants(t_lemin *lemin, int *amounts_of_ants, t_list *path, t_ant ant)
{
	t_ant	prev;
	int		i;
	t_ant	temp;

	i = -1;
	prev = ant;
	while (path)
	{
		if (DOBLE_DEREF(path)->type == END && prev.ant_id != NO_ANT)
		{
			amounts_of_ants[prev.way_id]++;
			lemin->end->ants_count++;
			break;
		}
		if (++i == 0)
		{
			prev = DOBLE_DEREF(path)->ant;
			DOBLE_DEREF(path)->ant = ant;
		}
		else if (prev.ant_id != NO_ANT)
		{
			temp = DOBLE_DEREF(path)->ant;
			DOBLE_DEREF(path)->ant = prev;
			prev = temp;
		}
		path = path->next;
	}
}

int		*ants_in_each_way(t_ant *ants_in_ways, t_lemin *lemin, t_list *paths)
{
	int		*res;
	int		i;
	int		j;

	res = (int *)malloc(sizeof(int) * list_size(paths));
	i = -1;
	while (++i < list_size(paths))
	{
		res[i] = 0;
		j = -1;
		while (++j < lemin->ants_count)
			if (ants_in_ways[j].way_id == i)
				res[i]++;
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

void	move_ants(t_lemin *lemin, char new_ant, t_list *path, t_ant ant)
{
	t_ant	prev;
	t_ant	temp;
	t_ant	*prev_ant;

	prev = DOBLE_DEREF(path)->ant;
	if (new_ant)
	{
		DOBLE_DEREF(path)->ant = ant;
		(DOBLE_DEREF(path)->type == END) ? lemin->end->ants_count++ : 0;
		ft_printf("L%d-%s ", DOBLE_DEREF(path)->ant.ant_id, DOBLE_DEREF(path)->name);
	}
	while (path->next)
	{
		prev_ant = &(DOBLE_DEREF(path)->ant);
		if (!new_ant)
			prev = *prev_ant;
		path = path->next;
		if (prev.ant_id != NO_ANT && prev.way_id != NO_ANT)
		{
			temp = prev;
			if (!new_ant)
			{
				prev_ant->ant_id = NO_ANT;
				prev_ant->way_id = NO_ANT;
				new_ant = 1;
			}
			prev = DOBLE_DEREF(path)->ant;
			DOBLE_DEREF(path)->ant = temp;
			(DOBLE_DEREF(path)->type == END) ? lemin->end->ants_count++ : 0;
			ft_printf("L%d-%s ", DOBLE_DEREF(path)->ant.ant_id, DOBLE_DEREF(path)->name);
		}
	}
}

void	display_movements(t_lemin *lemin, int *amounts_of_ants, t_list *paths)
{
	int 	i;
	t_list	*temp;
	int		ant_id;

	ant_id = 1;
	clear_paths(paths);
	while (lemin->end->ants_count != lemin->ants_count)
	{
		i = -1;
		temp = paths;
		while (++i < list_size(paths))
		{
			if (amounts_of_ants[i] > 0)
			{
				move_ants(lemin, 1, (*((t_list **)(temp->content)))->next, (t_ant){.ant_id = ant_id, .way_id = i});
				--(amounts_of_ants[i]);
				ant_id++;
			}
			else
				move_ants(lemin, 0, (*((t_list **)(temp->content)))->next, (t_ant){.ant_id = NO_ANT, .way_id = NO_ANT});
			temp = temp->next;
		}
		write(1, "\n", 1);
	}
}

void	scatter_ants(t_lemin *lemin, t_list *paths)
{
	int		*amounts_of_ants;
	int		ant_id;
	t_ant	ant;
	int		i;
	t_list	*temp;

	ant_id = 0;
	amounts_of_ants = (int *)malloc(list_size(paths) * sizeof(int));
	ft_bzero(amounts_of_ants, sizeof(int) * list_size(paths));
	while (lemin->end->ants_count != lemin->ants_count)
	{
		i = 0;
		temp = paths;
		while (paths && lemin->end->ants_count != lemin->ants_count)
		{
			ant.ant_id = ant_id;
			ant.way_id = i;
			update_ants(lemin, amounts_of_ants, (*((t_list **)(paths->content)))->next, ant);
			paths = paths->next;
			++ant_id;
			++i;
		}
		paths = temp;
	}
	lemin->end->ants_count = 0;
	display_movements(lemin, amounts_of_ants, paths);
	// free(amounts_of_ants);
}
