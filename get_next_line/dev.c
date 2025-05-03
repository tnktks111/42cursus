#include "get_next_line.h"
int main()
{
    char *s1;
    char *s2;
	char *s3;
    int fd;
    fd = open("1char.txt", O_RDONLY);
    s1 = get_next_line(fd);
    s2 = get_next_line(fd);
	s3 = get_next_line(fd);
    printf("%s%s%s", s1, s2, s3);
}