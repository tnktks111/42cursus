# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 00:30:32 by ttanaka           #+#    #+#              #
#    Updated: 2025/04/30 13:48:52 by ttanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

LIBFT_DIR = libft
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

INC = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) libft
	@cp $(LIBFT_DIR)/libft.a $(NAME)
	$(AR) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RMDIR) $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re libft