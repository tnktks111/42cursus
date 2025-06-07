#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define MALLOC_ERR -2
# define RD_ERR -3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_string
{
	char				*str;
	size_t				len;
	size_t				cap;
}						t_string;

typedef struct s_buf
{
	char				buf[BUFFER_SIZE];
	char				*bufp;
	int					bufsiz;
}						t_buf;

#endif