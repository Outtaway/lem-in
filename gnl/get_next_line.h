/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 10:19:12 by kpshenyc          #+#    #+#             */
/*   Updated: 2018/11/02 13:21:58 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include "../libftprintf/includes/ft_printf.h"
# define BUFF_SIZE 16
# define SHIT2 { temp = (str) ? str : NULL; str = NULL; }
# define SHIT3 { str = ft_strsub(slash + 1, 0, ft_strlen(slash + 1)); end = 1; }
# define SHIT4 { SHIT3; break ; }

int		get_next_line(const int fd, char **line);

#endif
