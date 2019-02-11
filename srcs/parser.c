/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:40:22 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/11 18:23:04 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_list	*create_farm_node(t_lemin *lemin, char *data, char type)
{
	t_farm				res;
	unsigned short		name_size;

	name_size = ft_strlen(data) - ft_strlen(ft_strchr(data, ' '));
	ft_strncpy(res.name, data, name_size);
	res.name[name_size] = 0;
	if (res.name[0] == 'L' || res.name[0] == '#')
		ERROR(4);
	res.x = ft_atoi(ft_strchr(data, ' '));
	res.y = ft_atoi(ft_strchr(ft_strchr(data, ' ') + 1, ' '));
	res.type = type;
	res.connections = NULL;
	res.state = UNMARKED;
	res.distance = type == START ? 0 : _USHRT_MAX;
	res.is_blocked = UNBLOCKED;
	res.ants_count = type == START ? lemin->ants_count : 0;
	res.ant.ant_id = NO_ANT;
	res.ant.way_id = NO_ANT;
	if (farm_exists(&res, lemin->farms))
		ERROR(9);
	return (ft_lstnew(&res, sizeof(res)));
}

void	set_connection(t_list *farms, char *line)
{
	t_list	*l_farm;
	t_list	*r_farm;

	*(ft_strchr(line, '-')) = 0;
	l_farm = get_node_by_name(farms, line);
	*(ft_strchr(line, '\0')) = '-';
	line = ft_strchr(line, '-') + 1;
	r_farm = get_node_by_name(farms, line);
	ft_lstadd(&(((t_farm *)(l_farm->content))->connections),
			ft_lstnew(r_farm, sizeof(r_farm)));
	ft_lstadd(&(((t_farm *)(r_farm->content))->connections),
			ft_lstnew(l_farm, sizeof(l_farm)));
}

void	set_start_end(t_lemin *lemin, char **line)
{
	char	type;
	int		ret;

	type = !ft_strcmp("##start", *line) ? START : END;
	ft_lstadd(&(lemin->input), ft_lstnew(line, sizeof(*line)));
	while ((ret = get_next_line(0, line, BUFF_SIZE)) > 0 && (*line)[0] == '#')
		ft_lstadd(&(lemin->input), ft_lstnew(&line, sizeof(line)));
	if (ret == 0)
		ERROR(413);
	if (!line_farm(*line))
		ERROR(2);
	ft_lstadd(&(lemin->farms), create_farm_node(lemin, *line, type));
	(type == START) ? (lemin->start = DEREF(lemin->farms)) :
			(lemin->end = (t_farm *)(lemin->farms->content));
}

void	get_lemin_struct(t_lemin *lemin, t_parser *parser)
{
	char	*line;

	while (get_next_line(0, &line, BUFF_SIZE) > 0)
	{
		if (line_farm(line) && parser->ants && !(parser->conn) &&
					(parser->rooms = 1))
			ft_lstadd(&(lemin->farms), create_farm_node(lemin, line, REGULAR));
		else if (line_connection(line) && parser->ants && parser->rooms &&
					(parser->conn = 1))
			set_connection(lemin->farms, line);
		else if ((!ft_strcmp("##start", line) || !ft_strcmp("##end", line)) &&
					(parser->rooms = 1))
			set_start_end(lemin, &line);
		else if (line_ants(line) && !(parser->ants) && (parser->ants = 1))
			lemin->ants_count = ft_atoi(line);
		else if (line[0] != '#')
			ERROR(3);
		ft_lstadd(&(lemin->input), ft_lstnew(&line, sizeof(line)));
	}
}
