NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_memmove.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror 
INC = -I.

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	ranlib $@

$(OBJS_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re