/*main.c*/

#include "get_next_line.h"

int	main(void)
{

	int		fd;
	char	*str;

	fd = open("aaafile", O_RDONLY);
	str = get_next_line(fd);
//	printf("get_next_line : >>%s<<\n", str);
//	printf("get_next_line : >>%s<<\n", get_next_line(fd));
//	printf("get_next_line : >>%s<<\n", get_next_line(fd));
	close(fd);
	free(str);
	return (0);
}
