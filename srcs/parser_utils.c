/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:12:42 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/11 18:41:03 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

char	farm_exists(t_farm *farm, t_list *farms)
{
	while (farms)
	{
		if (!ft_strcmp(DEREF(farms)->name, farm->name))
			return (1);
		if (DEREF(farms)->x == farm->x &&
				DEREF(farms)->y == farm->y)
			return (1);
		farms = farms->next;
	}
	return (0);
}

char	line_farm(char *line)
{
	unsigned short		i;
	unsigned short		j;

	i = 0;
	while (ft_strchr(line, ' '))
	{
		if (line[0] == '#')
			return (0);
		line = ft_strchr(line, ' ') + 1;
		j = 0;
		while (line[j] && line[j] != ' ')
		{
			if (line[j] < 48 || line[j] > 57)
				return (0);
			++j;
		}
		if (j == 0)
			return (0);
		++i;
	}
	if (i != 2)
		return (0);
	return (1);
}

char	line_ants(char *line)
{
	unsigned short	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 48 || line[i] > 57)
			return (0);
		++i;
	}
	return (1);
}

char	line_connection(char *line)
{
	char	iter;
	char	dashes;

	iter = -1;
	dashes = 0;
	while (line[++iter])
	{
		if (ftblank(line[iter]))
			return (0);
		else if (line[iter] == '-')
			dashes++;
	}
	if (dashes != 1)
		return (0);
	return (1);
}

t_list	*get_node_by_name(t_list *list, char *name)
{
	while (list)
	{
		if (!ft_strcmp(((t_farm *)list->content)->name, name))
			return (list);
		list = list->next;
	}
	ERROR(5);
	return (NULL);
}
