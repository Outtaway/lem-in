/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:12:42 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/04 13:13:54 by kpshenyc         ###   ########.fr       */
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
