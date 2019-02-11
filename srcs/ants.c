/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:28:26 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/11 18:35:20 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	start_end(t_lemin *lemin)
{
	while (lemin->end->ants_count != lemin->ants_count)
	{
		++lemin->end->ants_count;
		if (lemin->end->ants_count != lemin->ants_count)
			ft_printf("L%d-%s ", lemin->end->ants_count, lemin->end->name);
		else
			ft_printf("L%d-%s\n", lemin->end->ants_count, lemin->end->name);
	}
}

void	update_ants(t_lemin *lemin, int *amounts_of_ants,
					t_list *path, t_ant ant)
{
	t_ant	prev;
	int		i;

	i = -1;
	prev = ant;
	while (path)
	{
		if (DOBLE_DEREF(path)->type == END && prev.ant_id != NO_ANT)
		{
			amounts_of_ants[prev.way_id]++;
			lemin->end->ants_count++;
			break ;
		}
		if (++i == 0)
		{
			prev = DOBLE_DEREF(path)->ant;
			DOBLE_DEREF(path)->ant = ant;
		}
		else if (prev.ant_id != NO_ANT)
			SWAP(t_ant, DOBLE_DEREF(path)->ant, prev);
		path = path->next;
	}
}

void	move_ants(t_lemin *lemin, char new_ant, t_list *path, t_ant ant)
{
	t_ant	prev;

	prev = new_ant ? DOBLE_DEREF(path)->ant : (t_ant){.ant_id = NO_ANT,
														.way_id = NO_ANT};
	if (new_ant)
	{
		DOBLE_DEREF(path)->ant = ant;
		ft_printf("L%d-%s ",
			DOBLE_DEREF(path)->ant.ant_id, DOBLE_DEREF(path)->name);
		(DOBLE_DEREF(path)->type == END) ? lemin->end->ants_count++ : 0;
		path = path->next;
	}
	while (path)
	{
		ant = DOBLE_DEREF(path)->ant;
		DOBLE_DEREF(path)->ant = prev;
		prev = ant;
		if (DOBLE_DEREF(path)->ant.ant_id != NO_ANT)
		{
			ft_printf("L%d-%s ", DOBLE_DEREF(path)->ant.ant_id,
				DOBLE_DEREF(path)->name);
			(DOBLE_DEREF(path)->type == END) ? lemin->end->ants_count++ : 0;
		}
		path = path->next;
	}
}

void	display_movements(t_lemin *lemin, int *amounts_of_ants, t_list *paths)
{
	int		i;
	t_list	*temp;
	int		ant_id;

	ant_id = 0;
	clear_paths(paths);
	while (lemin->end->ants_count != lemin->ants_count)
	{
		i = -1;
		temp = paths;
		while (++i < list_size(paths))
		{
			if (amounts_of_ants[i] > 0)
			{
				move_ants(lemin, 1, (*((t_list **)(temp->content)))->next,
				(t_ant){.ant_id = ++ant_id, .way_id = i});
				--(amounts_of_ants[i]);
			}
			else
				move_ants(lemin, 0, (*((t_list **)(temp->content)))->next,
				(t_ant){.ant_id = NO_ANT, .way_id = NO_ANT});
			temp = temp->next;
		}
		write(1, "\n", 1);
	}
}

void	scatter_ants(t_lemin *lemin, t_list *paths)
{
	int		*amounts_of_ants;
	int		ant_id;
	int		i;
	t_list	*temp;

	ant_id = -1;
	amounts_of_ants = (int *)malloc(list_size(paths) * sizeof(int));
	ft_bzero(amounts_of_ants, sizeof(int) * list_size(paths));
	while (lemin->end->ants_count != lemin->ants_count)
	{
		i = -1;
		temp = paths;
		while (paths && lemin->end->ants_count != lemin->ants_count)
		{
			update_ants(lemin, amounts_of_ants,
				(*((t_list **)(paths->content)))->next,
			(t_ant){ .ant_id = ++ant_id, .way_id = ++i});
			paths = paths->next;
		}
		paths = temp;
	}
	lemin->end->ants_count = 0;
	display_movements(lemin, amounts_of_ants, paths);
	free(amounts_of_ants);
}
