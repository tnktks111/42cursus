# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 00:30:32 by ttanaka           #+#    #+#              #
#    Updated: 2025/05/05 11:56:48 by ttanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

SRCS_DIR = src
OBJS_DIR = obj
INC_DIR = inc

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RANLIB = ranlib
RM = rm -f
RMDIR = rm -rf

SRC_FILE_NAMES = ft_printf ft_printf_utils \
				 libft_for_ft_printf

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(SRC_FILE_NAMES)))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(SRC_FILE_NAMES)))

INC = -I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RMDIR) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft