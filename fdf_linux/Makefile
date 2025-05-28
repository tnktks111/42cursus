CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_PATH = mlx
MLX_LIB_FILE = $(MLX_PATH)/libmlx_Linux.a
MLX_FLAGS = -lXext -lX11 -lm

RM = rm -f
RM_DIR = rm -rf

NAME = fdf

INC_DIR = inc
INCLUDES = -I$(INC_DIR)

SRC_DIR_FDF = src
OBJ_DIR_FDF = obj_fdf
HEADER_FDF = $(INC_DIR)/fdf.h
HEADER_MLX_INC = $(INC_DIR)/mlx.h

SRCS_FILES_FDF = \
    00_main.c \
    01_parser.c \
    02_parser_helper.c \
    03_calculator.c \
    04_xiaolin_wu.c \
    05_line_drawer.c \
    06_hook_handler.c \
    07_menu.c \
    08_mouse.c \
    09_translation.c \
    10_redraw_and_reset.c \
    11_switch_view.c \
    17_quaternion_utils.c \
    17_quaternion_utils2.c \
    18_color.c \
    18_color2.c \
    19_init.c \
    20_free.c

SRCS_FDF = $(addprefix $(SRC_DIR_FDF)/, $(SRCS_FILES_FDF))
OBJS_FDF = $(patsubst $(SRC_DIR_FDF)/%.c,$(OBJ_DIR_FDF)/%.o,$(SRCS_FDF))

GNL_SRC_DIR = get_next_line
GNL_OBJ_DIR = obj_gnl
HEADER_GNL = $(INC_DIR)/get_next_line.h

SRCS_FILES_GNL = \
    get_next_line.c \
    get_next_line_utils.c

SRCS_GNL = $(addprefix $(GNL_SRC_DIR)/, $(SRCS_FILES_GNL))
OBJS_GNL = $(patsubst $(GNL_SRC_DIR)/%.c,$(GNL_OBJ_DIR)/%.o,$(SRCS_GNL))

LIBFT_SRC_DIR = libft_for_fdf
LIBFT_OBJ_DIR = obj_libft
HEADER_LIBFT = $(INC_DIR)/libft_for_fdf.h

SRCS_FILES_LIBFT = \
    ft_atoi_for_color.c \
    ft_atoi_for_fdf.c \
    ft_bzero.c \
    ft_init_int_buffer.c \
    ft_math_double.c \
    ft_math_int.c \
    ft_put_fd.c \
    ft_split.c \
    ft_strlen.c

SRCS_LIBFT = $(addprefix $(LIBFT_SRC_DIR)/, $(SRCS_FILES_LIBFT))
OBJS_LIBFT = $(patsubst $(LIBFT_SRC_DIR)/%.c,$(LIBFT_OBJ_DIR)/%.o,$(SRCS_LIBFT))

OBJS_ALL = $(OBJS_FDF) $(OBJS_GNL) $(OBJS_LIBFT)

all: $(NAME)

$(NAME): $(OBJS_ALL) $(MLX_LIB_FILE)
	$(CC) $(CFLAGS) $(OBJS_ALL) $(INCLUDES) $(MLX_LIB_FILE) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR_FDF)/%.o: $(SRC_DIR_FDF)/%.c $(HEADER_FDF) $(HEADER_MLX_INC) $(HEADER_GNL) $(HEADER_LIBFT) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_OBJ_DIR)/%.o: $(GNL_SRC_DIR)/%.c $(HEADER_GNL) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_SRC_DIR)/%.c $(HEADER_LIBFT) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM_DIR) $(OBJ_DIR_FDF)
	$(RM_DIR) $(GNL_OBJ_DIR)
	$(RM_DIR) $(LIBFT_OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re