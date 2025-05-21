# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 18:39:11 by ttanaka           #+#    #+#              #
#    Updated: 2025/05/21 18:55:52 by ttanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
RM_DIR = rm -rf

NAME = push_swap
SRC_DIR_MANDATORY = src
OBJ_DIR_MANDATORY = obj
INC_DIR_MANDATORY = inc
HEADER_MANDATORY = $(INC_DIR_MANDATORY)/push_swap.h

SRCS_FILES_MANDATORY = \
    00_main.c \
    01_argument_parser.c \
    02_lis.c \
    03_lis_helper.c \
    04_separator.c \
    05_insertion.c \
    06_insertion_helper.c \
    07_final_rotater.c \
    08_doubly_linked_list_utils.c \
    09_commands.c \
    10_libft_for_pushswap.c \
    11_list_utils.c \
    12_quick_sort.c \
    13_small_argc.c

SRCS_MANDATORY = $(addprefix $(SRC_DIR_MANDATORY)/, $(SRCS_FILES_MANDATORY))
OBJS_MANDATORY = $(patsubst $(SRC_DIR_MANDATORY)/%.c,$(OBJ_DIR_MANDATORY)/%.o,$(SRCS_MANDATORY))

INCLUDES_MANDATORY = -I$(INC_DIR_MANDATORY)

BONUS_NAME = checker
SRC_DIR_BONUS = bonus_src
OBJ_DIR_BONUS = bonus_obj
INC_DIR_BONUS = bonus_inc
HEADER_BONUS = $(INC_DIR_BONUS)/push_swap_bonus.h

GNL_DIR = get_next_line
SRC_DIR_GNL = $(GNL_DIR)/src
OBJ_DIR_GNL = $(GNL_DIR)/obj
INC_DIR_GNL = $(GNL_DIR)/inc
HEADER_GNL = $(INC_DIR_GNL)/get_next_line.h

SRCS_FILES_BONUS = \
    20_checker_bonus.c \
    21_argument_parser_bonus.c \
    22_doubly_linked_list_utils_bonus.c \
    23_commands_bonus.c \
    24_utils_for_checker.c \
    25_quick_sort.c

SRCS_FILES_GNL = \
    get_next_line.c \
    get_next_line_utils.c

SRCS_BONUS_ACTUAL = $(addprefix $(SRC_DIR_BONUS)/, $(SRCS_FILES_BONUS))
SRCS_GNL_ACTUAL = $(addprefix $(SRC_DIR_GNL)/, $(SRCS_FILES_GNL))

OBJS_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c,$(OBJ_DIR_BONUS)/%.o,$(SRCS_BONUS_ACTUAL))
OBJS_GNL = $(patsubst $(SRC_DIR_GNL)/%.c,$(OBJ_DIR_GNL)/%.o,$(SRCS_GNL_ACTUAL))

INCLUDES_BONUS_COMPILATION = -I$(INC_DIR_BONUS) -I$(INC_DIR_GNL)
INCLUDES_GNL_COMPILATION = -I$(INC_DIR_GNL)

all: $(NAME)

$(NAME): $(OBJS_MANDATORY) $(HEADER_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(INCLUDES_MANDATORY) -o $(NAME)

$(OBJ_DIR_MANDATORY)/%.o: $(SRC_DIR_MANDATORY)/%.c $(HEADER_MANDATORY) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES_MANDATORY) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_BONUS) $(OBJS_GNL) $(HEADER_BONUS) $(HEADER_GNL)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_GNL) $(INCLUDES_BONUS_COMPILATION) -o $(BONUS_NAME)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c $(HEADER_BONUS) $(HEADER_GNL) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS_COMPILATION) -c $< -o $@

$(OBJ_DIR_GNL)/%.o: $(SRC_DIR_GNL)/%.c $(HEADER_GNL) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES_GNL_COMPILATION) -c $< -o $@

clean:
	$(RM_DIR) $(OBJ_DIR_MANDATORY)
	$(RM_DIR) $(OBJ_DIR_BONUS)
	$(RM_DIR) $(OBJ_DIR_GNL)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus