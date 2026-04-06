# Nombre del proyecto
PROYECT = Libft

# Nombre del ejecutable o archivo final
NAME = libft.a

# Directorios PATH
BIN_PATH = ./bin
SRC_PATH = ./src
INCLUDE_PATH = ./include
BUILD_PATH = ./build
LIB_PATH = ./lib
CACHE = .bonus_cache

#Proyect .a
PROYECT_LIB_PATH = $(LIB_PATH)/$(PROYECT)

# Source Path
SRC_OBLIGATORY_PATH = $(SRC_PATH)/Obligatory
SRC_BONUS_PATH = $(SRC_PATH)/Bonus

# Obj Build Path
OBLIGATORY_BUILD_PATH = $(BUILD_PATH)/Obligatory
BONUS_BUILD_PATH = $(BUILD_PATH)/Bonus

#Archivos .h
INCLUDE_FILES_OBLIGATORY = libft.h
INCLUDE_FILES_BONUS = libft.h

# Include Path and Files
INCLUDE_PATH_FILES_OBLIGATORY = $(INCLUDE_PATH)/$(INCLUDE_FILES_OBLIGATORY)
INCLUDE_PATH_FILES_BONUS = $(INCLUDE_PATH)/$(INCLUDE_FILES_BONUS)

# Archivos .c (sin path)
C_FILES_OBLIGATORY =	ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c

C_FILES_BONUS = ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

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
	@echo "Creating Obligatory libft.a ..."
	@mkdir -p $(PROYECT_LIB_PATH) 
	@$(AR) $(PROYECT_LIB_PATH)/$(NAME) $(OBJS_OBLIGATORY)
	@echo "Completed"

# Compilación de los objetos obligatorios
$(OBLIGATORY_BUILD_PATH)/%.o: $(SRC_OBLIGATORY_PATH)/%.c $(INCLUDE_PATH_FILES_OBLIGATORY)
	@mkdir -p $(OBLIGATORY_BUILD_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus: banner $(CACHE)

# Compilación de los objetos bonus
$(CACHE): $(NAME) $(OBJS_BONUS)
	@echo "Creating Bonus libft.a ..."
	@mkdir -p $(PROYECT_LIB_PATH) 
	@$(AR) $(PROYECT_LIB_PATH)/$(NAME) $(OBJS_BONUS)
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

