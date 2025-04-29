#include "get_next_line.h"

int main(void) {
    int fd1;
    int fd2;

    fd1 = open("hungry.txt", O_RDONLY);
    fd2 = open("full.txt", O_RDONLY);
    printf("%s", get_next_line(fd1));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd1));
    printf("%s", get_next_line(fd2));
    printf("%s", get_next_line(fd1));
    printf("%s", get_next_line(fd2));
    close(fd1);
    close(fd2);
    return (0);
}