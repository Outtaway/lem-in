/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:28:07 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/02 18:03:56 by kpshenyc         ###   ########.fr       */
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
	// t_list		*temp;
	// t_farm		*farm;
	// t_list		*temp_2;

	ft_bzero(&lemin, sizeof(t_lemin));
	get_lemin_struct(&lemin);
	// temp_2 = lemin.farms;
	// while (temp_2)
	// {
	// 	temp = ((t_farm *)(temp_2->content))->connections;
	// 	ft_printf("%s %p\n", ((t_farm *)(temp_2->content))->name, (t_farm *)(temp_2->content));
	// 	while (temp)
	// 	{
	// 		farm = *((t_farm **)(temp->content));
	// 		ft_printf("%s\n", farm->name);
	// 		temp = temp->next;
	// 	}
	// 	temp_2 = temp_2->next;
	// }
	if (!lemin.start || !lemin.end)
		ERROR();
	bfs(&lemin);
	if (lemin.end->distance == _INT_MAX)
		ERROR();
	shortest_path(&lemin);
//	system("leaks lem-in");
	return (0);
}
