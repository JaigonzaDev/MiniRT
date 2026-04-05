# Project
NAME		= miniRT

# Detect operating system
UNAME_S		:= $(shell uname -s)

# Directories
SRC_DIR		= srcs
BUILD_DIR	= build
BIN_DIR		= .
INCLUDE_DIR	= include
MLX_DIR_LINUX	= libs/mlx_linux
# Prefer local macOS port if present, otherwise fallback to legacy path
MLX_DIR_MAC	= $(if $(wildcard mlx_macos/Makefile),mlx_macos,libs/mlx_mac)
MLX_DIR		= libs/mlx
GNL_DIR		= libs/Get_next_line
GNL_LIB		= $(GNL_DIR)/lib/libget_next_line.a

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
INCLUDES	= -I$(INCLUDE_DIR) -Ilibs/Get_next_line/include
RM			= rm -rf
SAN_FLAGS	= -fsanitize=address,undefined -fno-omit-frame-pointer

# OS-specific settings
ifeq ($(UNAME_S), Linux)
	MLX_DIR     = $(MLX_DIR_LINUX)
	INCLUDES    += -I$(MLX_DIR)
	LDFLAGS     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
endif
ifeq ($(UNAME_S), Darwin)
	MLX_DIR     = $(MLX_DIR_MAC)
	INCLUDES    += -I$(MLX_DIR)
	BREW_PATH   = $(shell brew --prefix 2>/dev/null)
	ifneq ($(BREW_PATH),)
		INCLUDES    += -I$(BREW_PATH)/include
		LDFLAGS     = -L$(MLX_DIR) -lmlx -L$(BREW_PATH)/lib -framework OpenGL -framework AppKit
	else
		LDFLAGS     = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	endif
endif

all: $(NAME)

sani: CFLAGS += $(SAN_FLAGS)
sani: LDFLAGS += $(SAN_FLAGS)
sani: re

info:
	@echo "Building for: $(UNAME_S)"
	@echo "MLX Directory: $(MLX_DIR)"
	@echo "LDFLAGS: $(LDFLAGS)"

$(MLX_DIR)/libmlx.a:
	@if [ -z "$(ls -A $(MLX_DIR))" ]; then \
		echo "MLX directory is empty, cloning repository..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@echo "Building MLX..."
	@make -C $(MLX_DIR)

$(GNL_LIB):
	@echo "Building Get_next_line..."
	@$(MAKE) -C $(GNL_DIR)

$(NAME): $(MLX_DIR)/libmlx.a $(GNL_LIB) $(OBJECTS)
	@echo "Linking $(NAME) for $(UNAME_S)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(GNL_LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) built successfully for $(UNAME_S)!"

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

re: fclean all

.PHONY: all clean fclean re info help