/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tantoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:39:23 by tantoni           #+#    #+#             */
/*   Updated: 2022/09/15 19:40:54 by tantoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	reindex_buffer(ssize_t seg_len, char *buf)
{
	ssize_t	i;

	if (seg_len == my_strlen(buf))
	{
		i = -1;
		while (buf[(++i)])
			buf[i] = 0;
		return ;
	}
	i = seg_len;
	while (i - seg_len < BUFFER_SIZE)
	{
		buf[i - seg_len] = 0;
		if (i < BUFFER_SIZE)
		{
			buf[i - seg_len] = buf[i];
			buf[i] = 0;
		}
		i++;
	}
}

static char	*pop_firstsegment(char *line, char *buf)
{
	char	*result;
	ssize_t	line_len;
	ssize_t	seg_len;
	ssize_t	i;

	line_len = my_strlen(line);
	seg_len = get_endindex(buf) + 1;
	if ((seg_len - 1) == -1)
		seg_len = my_strlen(buf);
	if (line_len == 0 && seg_len == 0)
		return (NULL);
	result = my_calloc(line_len + seg_len, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (line && line[(++i)])
		result[i] = line[i];
	i = -1;
	while (++i < seg_len && buf && buf[i])
		result[line_len + i] = buf[i];
	reindex_buffer(seg_len, buf);
	if (line)
		free(line);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	stash[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*buf;
	char		*line;
	ssize_t		readqty;
	size_t		i;

	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	i = -1;
	while ((++i) < FOPEN_MAX)
		if (i == (size_t)fd)
			buf = stash[i];
	readqty = 0;
	line = pop_firstsegment(NULL, buf);
	while (readqty != -1 && get_endindex(line) == -1)
	{
		if (my_strlen(buf) <= 0)
			readqty = read(fd, buf, BUFFER_SIZE);
		line = pop_firstsegment(line, buf);
		if (readqty <= 0 && my_strlen(buf) == 0)
			return (line);
	}
	return (line);
}
