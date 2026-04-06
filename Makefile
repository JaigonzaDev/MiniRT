# Project
NAME		= miniRT

# Directories
SRC_DIR		= srcs
BUILD_DIR	= build
BIN_DIR		= .
INCLUDE_DIR	= include
MLX_DIR		= libs/mlx_linux
GNL_DIR		= libs/Get_next_line
LIBFT_DIR	= libs/Libft
GNL_LIB		= $(GNL_DIR)/lib/libget_next_line.a
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source files
SOURCES		= main.c \
	cleanup.c \
Graph/mlx_init.c \
Graph/mlx_loop.c \
Objects/cylinder.c \
Objects/plane.c \
Objects/sphere.c \
Parse/parse_objects.c \
Parse/parse_objects2.c \
Parse/parse_objects3.c \
Parse/parse_file.c \
Parse/parse_physics.c \
Parse/parse_properties.c \
Parse/parse_utils.c \
render/color.c \
render/light.c \
render/pixel.c \
render/ray.c \
render/render.c \
render/render_utils.c \
Vector/vector_basic_operations.c \
Vector/vector_calculation_operations.c \
intersection/utils.c \
intersection/plane_intersection.c \
intersection/cylinder_intersection.c \
intersection/cylinder_intersection_utils.c \


# Object files
OBJECTS		= $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I$(INCLUDE_DIR) -I$(MLX_DIR) -I$(GNL_DIR)/include -I$(LIBFT_DIR)/include
LDFLAGS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -L$(LIBFT_DIR) -lft
RM			= rm -rf
SAN_FLAGS	= -fsanitize=address,undefined -fno-omit-frame-pointer

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

$(GNL_LIB):
	@echo "Building Get_next_line..."
	@$(MAKE) -C $(GNL_DIR)

$(LIBFT_LIB):
	@echo "Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MLX_DIR)/libmlx.a $(GNL_LIB) $(LIBFT_LIB) $(OBJECTS)
	@echo "Linking $(NAME)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(GNL_LIB) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) built successfully!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(BUILD_DIR)
	@if [ -f "$(MLX_DIR)/Makefile" ]; then \
		echo "Cleaning MLX build files..."; \
		$(MAKE) --no-print-directory -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true; \
	fi
	@if [ -f "$(GNL_DIR)/Makefile" ]; then \
		echo "Cleaning Get_next_line build files..."; \
		$(MAKE) --no-print-directory -s -C $(GNL_DIR) clean >/dev/null 2>&1 || true; \
	fi
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		echo "Cleaning Libft build files..."; \
		$(MAKE) --no-print-directory -s -C $(LIBFT_DIR) clean >/dev/null 2>&1 || true; \
	fi

fclean:
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@if [ -f "$(MLX_DIR)/Makefile" ]; then \
		$(MAKE) --no-print-directory -s -C $(MLX_DIR) fclean >/dev/null 2>&1 || \
		$(MAKE) --no-print-directory -s -C $(MLX_DIR) clean >/dev/null 2>&1 || true; \
	fi
	@if [ -f "$(GNL_DIR)/Makefile" ]; then \
		$(MAKE) --no-print-directory -s -C $(GNL_DIR) fclean >/dev/null 2>&1 || true; \
	fi
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) --no-print-directory -s -C $(LIBFT_DIR) fclean >/dev/null 2>&1 || true; \
	fi

re: fclean all

.PHONY: all clean fclean re info helpdofpkaafda