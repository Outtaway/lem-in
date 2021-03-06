/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:52:15 by kpshenyc          #+#    #+#             */
/*   Updated: 2018/10/24 13:52:16 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	while (s1[i])
		++i;
	while (s2[j] && j < n)
	{
		s1[i] = s2[j];
		++j;
		++i;
	}
	s1[i] = '\0';
	return (s1);
}
