/*get_next_line.c*/

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

static void reindex_buffer(ssize_t seg_len, char *buf)
{
	ssize_t	i;
	
	if (seg_len == my_strlen(buf))
	{
		i = -1;
		while((++i) < BUFFER_SIZE)
			buf[i] = 0;
		return ;
	}
	i = seg_len;
	while (i < BUFFER_SIZE)
	{
		buf[i - seg_len] = buf[i];
		buf[i] = 0;	
		i++;
	}
}
static char *pop_firstsegment(char *line, char *buf)
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
	return (result);
}

char	*get_next_line(int fd)
{
	static char	stash[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*buf;
	char		*line;
	ssize_t		readqty;
	size_t		i;

	if (fd > FOPEN_MAX)
		return (NULL);
	i = 0;
	while (i < FOPEN_MAX)
	{
		if (i == fd)
			buf = stash[i];
		i++;
	}
	readqty = 0;
	line = pop_firstsegment(NULL, buf);
	while (get_endindex(line) == -1)
	{
		if (my_strlen(buf) <= 0)
			readqty = read(fd, buf, BUFFER_SIZE);
		line = pop_firstsegment(line, buf);
		if (!readqty && !my_strlen(buf))
			return (line);
	}
	return (line);
}
