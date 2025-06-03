# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 20:48:19 by ttanaka           #+#    #+#              #
#    Updated: 2025/06/03 20:50:42 by ttanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

INC_DIR = ./inc
LIBFT_DIR = ./libft
LIBGNL_DIR = ./get_next_line
PIPEX_SRC_DIR = ./src
PIPEX_OBJ_DIR = ./obj

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(LIBGNL_DIR)

PIPEX_SRC_BASENAMES = 00_main.c \
                      01_parse_file.c \
                      02_exec_commands.c \
                      03_exec_helper.c \
                      04_ft_getenv.c \
                      05_gen_str.c \
                      06_notify.c \
					  07_free.c

PIPEX_SRCS = $(addprefix $(PIPEX_SRC_DIR)/, $(PIPEX_SRC_BASENAMES))
PIPEX_OBJS = $(addprefix $(PIPEX_OBJ_DIR)/, $(PIPEX_SRC_BASENAMES:.c=.o))

LIBFT_A = $(LIBFT_DIR)/libft.a
LIBGNL_A = $(LIBGNL_DIR)/libgnl.a

LDFLAGS_LIBFT = -L$(LIBFT_DIR) -lft
LDFLAGS_LIBGNL = -L$(LIBGNL_DIR) -lgnl

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT_DIR)

$(LIBGNL_A):
	$(MAKE) -s -C $(LIBGNL_DIR)

$(NAME): $(PIPEX_OBJS) $(LIBFT_A) $(LIBGNL_A)
	$(CC) $(CFLAGS) $(PIPEX_OBJS) $(LDFLAGS_LIBFT) $(LDFLAGS_LIBGNL) -o $(NAME)

$(PIPEX_OBJ_DIR)/%.o: $(PIPEX_SRC_DIR)/%.c $(INC_DIR)/pipex.h Makefile
	mkdir -p $(PIPEX_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(PIPEX_OBJS)
	rm -rf $(PIPEX_OBJ_DIR)
	$(MAKE) -s -C $(LIBFT_DIR) clean
	$(MAKE) -s -C $(LIBGNL_DIR) clean

fclean:
	rm -f $(PIPEX_OBJS)
	rm -rf $(PIPEX_OBJ_DIR)
	rm -f $(NAME)
	$(MAKE) -s -C $(LIBFT_DIR) fclean
	$(MAKE) -s -C $(LIBGNL_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus