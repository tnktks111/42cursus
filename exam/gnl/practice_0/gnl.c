#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#define RD_ERR -2
#define MALLOC_ERR -3
typedef struct s_string{
    char *str;
    int len;
    int cap;
}t_string;

typedef struct s_buffer{
    char buffer[BUFFER_SIZE];
    char *bufp;
    char bufsiz;
} t_buffer;

void ft_bzero(void *s, size_t n)
{
    if (!s || n == 0)
        return ;
    unsigned char *us = (unsigned char *)s;
    unsigned int i = 0;
    while (i < n)
        us[i++] = 0;
}

void *ft_memmove(void *dst, const void *src, size_t len)
{
    size_t i;
    unsigned char *dst_cpy = (unsigned char *)dst;
    unsigned char *src_cpy = (unsigned char *)src;
    if (!dst || !src || dst == src)
        return (dst);
    if (dst < src)
    {
        i = 0;
        while (i < len)
        {
            dst_cpy[i] = src_cpy[i];
            i++;
        }
    }
    else
    {
        i = len;
        while (i > 0)
        {
            i--;
            dst_cpy[i] = src_cpy[i];
        }
    }
    return (dst);
}

int ft_getc(int fd, t_buffer *buffer)
{
    int bytes;

    if (buffer->bufsiz == 0)
    {
        ft_bzero(buffer->buffer, BUFFER_SIZE);
        bytes = read(fd, buffer->buffer, BUFFER_SIZE);
        if (bytes == 0)
            return (EOF);
        if (bytes == -1)
            return (RD_ERR);
        buffer->bufp = buffer->buffer;
        buffer->bufsiz = bytes;
    }
    buffer->bufsiz--;
    return (*(buffer->bufp++));
}

int ft_putc(char c, t_string *str)
{
    char *new_str;
    if (str->len == 0)
    {
        str->str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        if (!str->str)
            return (MALLOC_ERR);
        str->len = 0;
        str->cap = BUFFER_SIZE;
    }
    if (str->len + 1 == str->cap)
    {
        new_str = (char *)malloc(sizeof(char) * (str->cap * 2));
        if (!new_str)
        {
            free(str->str);
            return (MALLOC_ERR);
        }
        ft_memmove(new_str, str->str, str->len);
        free(str->str);
        str->str = new_str;
        str->cap *= 2;
    }
    str->str[str->len++] = c;
    return (EXIT_SUCCESS);
}

char *get_next_line(int fd)
{
    t_string str = {NULL, 0, 0};
    static t_buffer buffer;
    int c;

    if (fd < 0)
        return (NULL);
    while (1)
    {
        c = ft_getc(fd, &buffer);
        if (c == RD_ERR)
        {
            free(str.str);
            return (NULL);
        }
        if (c == EOF)
            break;
        if (ft_putc((char)c, &str) == MALLOC_ERR)
        {
            free(str.str);
            return (NULL);
        }
        if (c == '\n')
            break;
    }
    if (!str.len)
        return (NULL);
    if (ft_putc('\0', &str) == MALLOC_ERR)
    {
        free(str.str);
        return (NULL);
    }
    return (str.str);
}

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *s = get_next_line(fd);
    while (s)
    {
        printf("%s", s);
        free(s);
        s = get_next_line(fd);
    }
    close(fd);
}