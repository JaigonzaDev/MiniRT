# Nombre del proyecto
PROYECT = Get_next_line 

# Nombre del ejecutable o archivo final
NAME = libget_next_line.a

# Directorios PATH
BIN_PATH = ./bin
SRC_PATH = ./src
INCLUDE_PATH = ./include
BUILD_PATH = ./build
LIB_PATH = ./lib
CACHE = .bonus_cache

# Proyect .a
PROYECT_LIB_PATH = $(LIB_PATH)
PROYECT_LIB = $(LIB_PATH)/$(NAME)

# Source Path
SRC_OBLIGATORY_PATH = $(SRC_PATH)/Obligatory
SRC_BONUS_PATH = $(SRC_PATH)/Bonus

# Obj Build Path
OBLIGATORY_BUILD_PATH = $(BUILD_PATH)/Obligatory
BONUS_BUILD_PATH = $(BUILD_PATH)/Bonus

# Archivos .h
INCLUDE_FILES_OBLIGATORY = get_next_line.h
INCLUDE_FILES_BONUS = get_next_line_bonus.h

# Include Path and Files
INCLUDE_PATH_FILES_OBLIGATORY = $(INCLUDE_PATH)/$(INCLUDE_FILES_OBLIGATORY)
INCLUDE_PATH_FILES_BONUS = $(INCLUDE_PATH)/$(INCLUDE_FILES_BONUS)

# Archivos .c (sin path)
C_FILES_OBLIGATORY = get_next_line.c get_next_line_utils.c

C_FILES_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

# Archivos .c (con path)
SRCS_OBLIGATORY = $(addprefix $(SRC_OBLIGATORY_PATH)/, $(C_FILES_OBLIGATORY))
SRCS_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(C_FILES_BONUS))

# Conversion archivos .c en .o
OBJS_OBLIGATORY = $(patsubst $(SRC_OBLIGATORY_PATH)/%.c, $(OBLIGATORY_BUILD_PATH)/%.o, $(SRCS_OBLIGATORY))
OBJS_BONUS = $(patsubst $(SRC_BONUS_PATH)/%.c, $(BONUS_BUILD_PATH)/%.o, $(SRCS_BONUS))

# Compilador y flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs
RM = rm -rf

# Reglas
all: banner $(NAME)

$(NAME): $(OBJS_OBLIGATORY)
	@echo "Creating Obligatory..."
	@mkdir -p $(PROYECT_LIB_PATH) 
	@$(AR) $(PROYECT_LIB) $(OBJS_OBLIGATORY)
	@echo "Completed"

# Compilación de los objetos obligatorios
$(OBLIGATORY_BUILD_PATH)/%.o: $(SRC_OBLIGATORY_PATH)/%.c $(INCLUDE_PATH_FILES_OBLIGATORY)
	@mkdir -p $(OBLIGATORY_BUILD_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus: banner $(CACHE)

# Compilación de los objetos bonus
$(CACHE): $(NAME) $(OBJS_BONUS)
	@echo "Creating Bonus..."
	@mkdir -p $(PROYECT_LIB_PATH) 
	@$(AR) $(PROYECT_LIB) $(OBJS_BONUS)
	@touch $(CACHE)
	@echo "Completed"

$(BONUS_BUILD_PATH)/%.o: $(SRC_BONUS_PATH)/%.c $(INCLUDE_PATH_FILES_BONUS)
	@mkdir -p $(BONUS_BUILD_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

clean:
	@$(RM) $(BUILD_PATH)
	@$(RM) $(CACHE)

fclean: clean
	@$(RM) $(LIB_PATH)

re: fclean all

# Banner
banner:
	@echo ':::::::::::     :::     :::::::::::  ::::::::   ::::::::  ::::    ::: :::::::::     :::    '
	@echo '    :+:       :+: :+:       :+:     :+:    :+: :+:    :+: :+:+:   :+:      :+:    :+: :+:  '
	@echo '    +:+      +:+   +:+     +:+     +:+     +:+        +:+    +:+ :+:+:+  +:+      +:+   +:+ '
	@echo '    +#+     +#++:++#++:     +#+     :#:        +#+    +:+ +#+ +:+ +#+    +#+    +#++:++#++: '
	@echo '    +#+     +#+     +#+     +#+     +#+   +#+# +#+    +#+ +#+  +#+#+#   +#+     +#+     +#+ '
	@echo '#+# #+#     #+#     #+#     #+#     #+#    #+# #+#    #+# #+#   #+#+#  #+#      #+#     #+# '
	@echo ' #####      ###     ### ###########  ########   ########  ###    #### ######### ###     ###'

.PHONY: all clean fclean re banner bonus

