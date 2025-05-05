/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:58:35 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/04 23:21:29 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

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
t_buf_list *create_t_buf_list_node(int fd);
void free_node(t_buf_list *node);

#endif