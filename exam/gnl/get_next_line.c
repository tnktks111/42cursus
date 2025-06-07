#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;

	if (!s)
		return ;
	c = (unsigned char *)s;
	while (n)
	{
		*c++ = 0;
		n--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	i;

	if (!dst || !src)
		return (dst);
	dst_cpy = (char *)dst;
	src_cpy = (char *)src;
	if (!len || dst == src)
		return (dst);
	if (dst_cpy < src_cpy)
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
		while (len-- > 0)
			dst_cpy[len] = src_cpy[len];
	}
	return (dst);
}

int	ft_getc(int fd, t_buf *buffer)
{
	if (buffer->bufsiz <= 0)
	{
		ft_bzero(buffer->buf, BUFFER_SIZE);
		buffer->bufsiz = read(fd, buffer->buf, BUFFER_SIZE);
		buffer->bufp = buffer->buf;
		if (buffer->bufsiz < 0)
			return (RD_ERR);
		if (buffer->bufsiz == 0)
			return (EOF);
	}
	(buffer->bufsiz)--;
	return ((unsigned char)(*(buffer->bufp)++));
}

int	ft_putc(t_string *str, char c)
{
	char	*newstr;

	if (str->cap == 0)
	{
		str->str = malloc(BUFFER_SIZE);
		if (!(str->str))
			return (MALLOC_ERR);
		ft_bzero(str->str, BUFFER_SIZE);
		str->len = 0;
		str->cap = BUFFER_SIZE;
	}
	else if (str->len >= str->cap)
	{
		newstr = malloc(str->cap * 2);
		if (!newstr)
			return (MALLOC_ERR);
		ft_bzero(newstr, str->cap * 2);
		ft_memmove(newstr, str->str, str->len);
		free(str->str);
		str->str = newstr;
		str->cap *= 2;
	}
	str->str[(str->len)++] = c;
	return (0);
}

char	*get_next_line(int fd)
{
    static t_buf    buffer;
	t_string        res = {NULL, 0, 0};
    int             c;

	if (fd < 0)
		return (NULL);
	while (1)
	{
		c = ft_getc(fd, &buffer);
		if (c == RD_ERR)
		{
			if (res.str)
				free(res.str);
			return (NULL);
		}
		if (c == EOF)
			break;
		if (ft_putc(&res, (char)c) == MALLOC_ERR)
		{
			if (res.str)
				free(res.str);
			return (NULL);
		}
		if ((char)c == '\n')
			break;
	}
	return (res.str);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *s;
	while ((s = get_next_line(fd)))
	{
		printf("%s", s);
		free(s);
	}
}