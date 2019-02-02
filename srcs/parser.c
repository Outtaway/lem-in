/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:40:22 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/02 18:16:29 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

char	line_numeric(char *line, char two_blanks)
{
	char	iter;
	char	blanks;
	char	word;

	blanks = 0;
	iter = -1;
	word = 0;
	while (line[++iter])
	{
		if (two_blanks && ftblank(line[iter]) && !word)
			word = 1;
		else if (word && two_blanks && !ft_isdigit(line[iter]) &&
				!ftblank(line[iter]))
			return (0);
		else if (!two_blanks && !ft_isdigit(line[iter]))
			return (0);
		ftblank(line[iter]) ? ++blanks : 0;
	}
	if (two_blanks && blanks != 2)
		return (0);
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

t_list	*create_farm_node(char *data, char type)
{
	t_farm	res;
	int 	name_size;

	name_size = ft_strlen(data) - ft_strlen(ft_strchr(data, ' '));
	ft_strncpy(res.name, data, name_size);
	if (res.name[0] == 'L')
		ERROR();
	res.name[name_size] = 0;
	res.x = ft_atoi(ft_strchr(data , ' '));
	res.y = ft_atoi(ft_strchr(ft_strchr(data, ' ') + 1, ' '));
	res.type = type;
	res.connections = NULL;
	res.state = UNMARKED;
	res.distance = type == START ? 0 : _INT_MAX;
	res.is_blocked = UNBLOCKED;
	return (ft_lstnew(&res, sizeof(res)));
}

t_list	*get_node_by_name(t_list *list, char *name)
{
	while (list)
	{
		if (ft_strequ(((t_farm *)list->content)->name, name))
			return (list);
		list = list->next;
	}
	ERROR();
	return (NULL);
}

void	set_connection(t_list *farms, char *line)
{
	char	*name_temp;
	t_list	*l_farm;
	t_list	*r_farm;
	t_list	*temp;

	name_temp = ft_strsub(line, 0, ft_strlen(line)
				- ft_strlen(ft_strchr(line, '-')));
	l_farm = get_node_by_name(farms, name_temp);
	ft_strdel(&name_temp);
	name_temp = ft_strsub(line, ft_strlen(line) - ft_strlen(ft_strchr(line, '-'))
				+ 1,ft_strlen(ft_strchr(line, '-')));
	r_farm = get_node_by_name(farms, name_temp);
	temp = ft_lstnew(r_farm, sizeof(r_farm));
	ft_lstadd(&(((t_farm *)(l_farm->content))->connections), temp);
	temp = ft_lstnew(l_farm, sizeof(l_farm));
	ft_lstadd(&(((t_farm *)(r_farm->content))->connections), temp);
	ft_strdel(&name_temp);
}

void	get_lemin_struct(t_lemin *lemin)
{
	char	*line;
	char	type;

	get_next_line(0, &line);
	if ((lemin->ants_count = ft_atoi(line)) == 0)
		ERROR();
	ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		if (line_numeric(line, 1))
			ft_lstadd(&(lemin->farms), create_farm_node(line, REGULAR));
		else if (line_connection(line))
			set_connection(lemin->farms, line);
		else if (!ft_strcmp("##start", line) || !ft_strcmp("##end", line))
		{
			type = !ft_strcmp("##start", line) ? START : END;
			DEL_GET(line);
			ft_lstadd(&(lemin->farms), create_farm_node(line, type));
			if (type == START)
				lemin->start = (t_farm *)(lemin->farms->content);
			else
				lemin->end = (t_farm *)(lemin->farms->content);
		}
		else if (line[0] != '#')
			ERROR();
		ft_strdel(&line);
	}
}
