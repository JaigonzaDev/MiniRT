# Project
NAME		= miniRT

# Directories
SRC_DIR		= source
BUILD_DIR	= build
BIN_DIR		= bin
INCLUDE_DIR	= include
LIB_DIR		= libs/libft

# Source files organized by modules
SOURCES		= main.c \
graph/mlx_init.c \
objects/cylinder.c \
objects/plane.c \
objects/sphere.c \
parse/parse_objects.c \
parse/physics.c \
parse/properties.c \
parse/parse_utils.c \
render/color.c \
render/light.c \
render/pixel.c \
render/ray.c \
render/render.c \
vector/vector_basic_operations.c \
vector/vector_calculation_operations.c \

# Object files
OBJECTS		= $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Libraries
LIBFT		= $(LIB_DIR)/libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I$(INCLUDE_DIR) -I$(LIB_DIR)/include
RM			= rm -rf

# System detection for readline
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	# macOS
	READLINE_PATH = $(shell brew --prefix readline 2>/dev/null || echo "/opt/homebrew")
	INCLUDES += -I$(READLINE_PATH)/include
	LDFLAGS = -L$(READLINE_PATH)/lib -L$(LIB_DIR)
else
	# Linux
	LDFLAGS = -L$(LIB_DIR)
endif

LIBS		= $(LDFLAGS) -lft -lreadline -lncurses -lm

# ================================== RULES =================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "Linking $(NAME)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BIN_DIR)/$(NAME)
	@echo "$(NAME) built successfully!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIB_DIR)

libft:
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo "Cleaning object files..."
	@$(RM) $(BUILD_DIR)

fclean: clean
	@echo "Cleaning all generated files..."
	@$(RM) $(BIN_DIR)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft show