/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tantoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:38:36 by tantoni           #+#    #+#             */
/*   Updated: 2022/09/15 19:38:48 by tantoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*my_calloc(ssize_t elems, ssize_t size)
{
	char	*result;
	ssize_t	i;

	result = malloc((elems + 1) * size);
	if (!result)
		return (NULL);
	i = -1;
	while ((++i) < (elems + 1) * size)
		result[i] = 0;
	return (result);
}

ssize_t	my_strlen(char *str)
{
	ssize_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

ssize_t	get_endindex(char *str)
{
	ssize_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
