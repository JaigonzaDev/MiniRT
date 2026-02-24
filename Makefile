# Project
NAME		= miniRT

# Directories
SRC_DIR		= .
BUILD_DIR	= build
BIN_DIR		= bin
INCLUDE_DIR	= .

# Source files
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
lib/Get_next_line/src/Obligatory/get_next_line.c \
lib/Get_next_line/src/Obligatory/get_next_line_utils.c

# Object files
OBJECTS		= $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I$(INCLUDE_DIR) -Ilib/Get_next_line/include
RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking $(NAME)..."
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(BIN_DIR)/$(NAME)
	@echo "$(NAME) built successfully!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(RM) $(BUILD_DIR)

fclean: clean
	@echo "Cleaning all generated files..."
	@$(RM) $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re libft