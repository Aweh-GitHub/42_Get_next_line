/*main.c*/

#include "get_next_line.h"

int	main(void)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open("bugfile", O_RDONLY);
	while (i < 5)
	{
		str = get_next_line(fd);
//		printf("%s\n", str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}
