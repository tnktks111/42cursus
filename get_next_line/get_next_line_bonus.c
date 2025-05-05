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

void free_node(t_buf_list *node)
{
    if (!node)
        return ;
    if (node->content)
    {
        if (node->content->buf)
        {
            free(node->content->buf);
            node->content->buf = NULL;
        }
        free(node->content);
        node->content = NULL;
    }
    free(node);
}

int ft_getc_fd(int fd)
{
    static t_buf_list *head = NULL;
    t_buf_list *curr;
    t_buf_list *prev;
    t_buf *curr_buf;

    prev = NULL;
    curr = head;
    while (curr)
    {
        if (curr->fd == fd)
            break;
        prev = curr;
        curr = curr->nxt;
    }
    if (!curr)
    {
        curr = create_t_buf_list_node(fd);
        if (!curr)
            return (MALLOC_ERR);
        curr->nxt = head;
        head = curr;
        prev = NULL;
    }
    curr_buf = (curr->content);
    if (curr_buf->bufsiz <= 0)
    {
        if (!(curr_buf->buf))
        {
            curr_buf->buf = malloc(BUFFER_SIZE);
            if (!(curr_buf->buf))
            {
                if (prev)
                    prev->nxt = curr->nxt;
                else
                    head = curr->nxt;
                free_node(curr);
                return (MALLOC_ERR);
            }
            curr_buf->bufp = curr_buf->buf;
            curr_buf->bufsiz = 0;
        }
        curr_buf->bufsiz = read(fd, curr_buf->buf, BUFFER_SIZE);
        curr_buf->bufp = curr_buf->buf;
        if (curr_buf->bufsiz < 0)
        {
            if (prev)
                prev->nxt = curr->nxt;
            else
                head = curr->nxt;
            free_node(curr);
            return (RD_ERR);
        }
        if (curr_buf->bufsiz == 0)
        {
            if (prev)
                prev->nxt = curr->nxt;
            else
                head = curr->nxt;
            free_node(curr);
            return (EOF);
        }
    }
    (curr_buf->bufsiz)--;
    return ((unsigned char)(*(curr_buf->bufp)++));
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
    if (str->cap == 0)
    {
        str->str = malloc(BUFFER_SIZE);
        if (!(str->str))
            return (MALLOC_ERR);
        str->len = 0;
        str->cap = BUFFER_SIZE;
    }
    else if (str->len >= str->cap)
    {
        newstr = malloc(str->cap * 2);
        if (!newstr)
            return(MALLOC_ERR);
        ft_memmove(newstr, str->str, str->len);
        free(str->str);
        str->str = newstr;
        str->cap *= 2;
    }
    str->str[(str->len)++] = c;
    return (0);
}

char *get_next_line(int fd)
{
    t_string res;
    char     *final_str;
    int c;

    if (fd < 0)
        return NULL;
    res.str = NULL;
    res.len = 0;
    res.cap = 0;
    while (1)
    {
        c = ft_getc_fd(fd);
        if (c == MALLOC_ERR || c == RD_ERR)
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
    if (res.len == 0)
    {
        if (res.str)
            free(res.str);
        return (NULL);
    }
    final_str = (char *)malloc(sizeof(char) * (res.len + 1));
    if (!final_str)
    {
        free(res.str);
        return (NULL);
    }
    ft_memmove(final_str, res.str, res.len);
    final_str[res.len] = '\0';
    free(res.str);
    return (final_str);
}
