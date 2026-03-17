# Project
NAME		= miniRT

# Detect operating system
UNAME_S		:= $(shell uname -s)

# Directories
SRC_DIR		= .
BUILD_DIR	= build
BIN_DIR		= .
INCLUDE_DIR	= .
MLX_DIR_LINUX	= mlx
# Prefer local macOS port if present, otherwise fallback to legacy path
MLX_DIR_MAC	= $(if $(wildcard mlx_macos/Makefile),mlx_macos,lib/mlx)
MLX_DIR		= $(MLX_DIR_LINUX)

# Source files
SOURCES		= main.c \
	cleanup.c \
Graph/mlx_init.c \
Objects/cylinder.c \
Objects/plane.c \
Objects/sphere.c \
Parse/parse_objects.c \
Parse/parse_physics.c \
Parse/parse_properties.c \
Parse/parse_utils.c \
render/color.c \
render/light.c \
render/pixel.c \
render/ray.c \
render/render.c \
render/save_image.c \
Vector/vector_basic_operations.c \
Vector/vector_calculation_operations.c \
intersection/utils.c \
intersection/sphere_intersection.c \
intersection/plane_intersection.c \
intersection/cylinder_intersection.c \
lib/Get_next_line/src/Obligatory/get_next_line.c \
lib/Get_next_line/src/Obligatory/get_next_line_utils.c

# Object files
OBJECTS		= $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I$(INCLUDE_DIR) -Ilib/Get_next_line/include
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
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Error: MLX directory not found!"; \
		echo ""; \
		if [ "$(UNAME_S)" = "Linux" ]; then \
			echo "For Linux, clone MLX:"; \
			echo "  git clone https://github.com/42Paris/minilibx-linux.git mlx"; \
			echo "  cd mlx && make"; \
		elif [ "$(UNAME_S)" = "Darwin" ]; then \
			echo "For macOS, clone MLX:"; \
			echo "  git clone https://github.com/42Paris/minilibx-linux.git mlx"; \
			echo "  cd mlx && make"; \
			echo ""; \
			echo "Or install via package manager if available"; \
		fi; \
		exit 1; \
	fi
	@echo "Building MLX..."
	@make -C $(MLX_DIR)

$(NAME): $(MLX_DIR)/libmlx.a $(OBJECTS)
	@echo "Linking $(NAME) for $(UNAME_S)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) built successfully for $(UNAME_S)!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(BUILD_DIR)

fclean: clean
	@echo "Cleaning all generated files..."
	@$(RM) $(NAME)

re: fclean all

help:
	@echo "MiniRT Makefile - Cross-platform build system"
	@echo ""
	@echo "Usage:"
	@echo "  make           - Build the project"
	@echo "  make clean     - Remove object files"
	@echo "  make fclean    - Remove all generated files"
	@echo "  make re        - Rebuild the project"
	@echo "  make info      - Show build configuration"
	@echo "  make help      - Show this help message"
	@echo ""
	@echo "Supported platforms: Linux, macOS"
	@echo "Current platform: $(UNAME_S)"

.PHONY: all clean fclean re info help