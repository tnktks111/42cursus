#include "get_next_line.h"

t_buf_list *create_t_buf_list_node(int fd)
{
    t_buf_list *newbuf;
    newbuf = (t_buf_list*)malloc(sizeof(t_buf_list));
    if (!newbuf)
        return (NULL);
    newbuf->content = (t_buf *)malloc(sizeof(t_buf));
    if (!(newbuf->content))
    {
        free(newbuf);
        return (NULL);
    }
    newbuf->content->buf = NULL;
    newbuf->content->bufp = NULL;
    newbuf->content->bufsiz = 0;
    newbuf->fd = fd;
    newbuf->nxt = NULL;
    return (newbuf);
}

int free_node_and_return_malloc_err(t_buf_list *node)
{
    if (!node)
        return (MALLOC_ERR);
    (node->prv)->nxt = node->nxt;
    (node->nxt)->prv = node->prv;
    if (node->content)
    {
        if (node->content->buf)
            free(node->content->buf);
        free(node->content);
    }
    free(node);
    return (MALLOC_ERR);
}

int ft_getc_fd(int fd)
{
    static t_buf_list bufl = {NULL, NULL, -1};
    t_buf_list *cur;
    t_buf *cur_buf;
    cur = &bufl;
    while (cur->nxt)
    {
        if (cur->fd == fd)
            break;
        cur = cur->nxt;
    }
    if (cur->fd != fd)
    {
        cur->nxt = create_t_buf_list_node(fd);
        if (!(cur->nxt))
            return 
        cur = cur->nxt;
    }
    cur_buf = (cur->content);
    if (cur_buf->bufsiz <= 0)
    {
        if (!(cur_buf->buf))
        {
            cur_buf->buf = malloc(BUFFER_SIZE);
            if (!(cur_buf->buf))
                return (free_t_buf_list_and_return_err(bufl.next));
        }
        cur_buf->bufsiz = read(fd, cur_buf->buf, BUFFER_SIZE);
        if (cur_buf->bufsiz < 0)
        {
            free(cur_buf->buf);
            cur_buf->buf = NULL;
            cur_buf->bufp = NULL;
            cur_buf->bufsiz = 0;
            return (RD_ERR);
        }
        if (cur_buf->bufsiz == 0)
            return (EOF);
        cur_buf->bufp = cur_buf->buf;
    }
    (cur_buf->bufsiz)--;
    return ((unsigned char)(*(cur_buf->bufp)++));
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
			dst_cpy[i++] = *src_cpy++;
	}
	else
	{
		while (len > 0)
		{
			len--;
			dst_cpy[len] = src_cpy[len];
		}
	}
	return (dst);
}

int ft_putc(t_string *str, char c)
{
    char *newstr;
    if (!(str->len))
    {
        str->str = malloc(BUFFER_SIZE);
        if (!(str->str))
            return (MALLOC_ERR);
        str->len = 0;
        str->cap = BUFFER_SIZE;
    }
    else if (str->len + 1 > str->cap)
    {
        newstr = malloc(str->cap * 2);
        if (!newstr)
            return(1);
        ft_memmove(newstr, str->str, str->len);
        free(str->str);
        str->str = newstr;
        str->cap *= 2;
    }
    str->str[(str->len)] = c;
    if (c != '\0')
        str->len++;
    return (0);
}

char *get_next_line(int fd)
{
    t_string res;
    char c;

    res.str = NULL;
    res.len = 0;
    res.cap = 0;
    while (1)
    {
        c = ft_getc_fd(fd);
        if (c == MALLOC_ERR || c == RD_ERR)
            return (NULL);
        if (c == EOF)
            break;
        ft_putc(&res, c);
        if (c == '\n')
            break;
    }
    if (res.str == NULL || c == RD_ERR)
        return NULL;
    if (res.len > 0)
        ft_putc(&res, '\0');
    return res.str;
}
