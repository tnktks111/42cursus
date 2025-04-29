
#define EOF -1
#define MALLOC_ERR -2
#define RD_ERR -3
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1024
#endif

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_buf
{
    char *buf;
    char *bufp;
    int  bufsiz;
} t_buf;

typedef struct s_buf_list
{
    t_buf *content;
    struct s_buf_list *nxt;
    struct s_buf_list *prv;
    int fd;
} t_buf_list;

typedef struct s_string
{
    char *str;
    size_t len;
    size_t cap;
} t_string;

int     ft_getc_fd(int fd);
void	*ft_memmove(void *dst, const void *src, size_t len);
int     ft_putc(t_string *str, char c);
char    *get_next_line(int fd);
