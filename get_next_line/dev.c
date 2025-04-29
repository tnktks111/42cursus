#include "get_next_line.h"
int main()
{
    char *s2;
    char *s4;
    int fd;
    fd = open("test.txt", O_RDONLY);
    s2 = get_next_line(fd);
    s4 = get_next_line(fd);
    printf("%s%s", s2, s4);
}