# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/02/22 15:24:40 by tishihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES


NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

SRC_DIR			= src
OBJ_DIR			= obj


# **************************************************************************** #
# SOURCES
SRC_UTILS		= \
				utils.c \

SRC_AST			= \
				exec_ast.c \

SRC				= \
				main.c \
				$(addprefix utils/, $(SRC_UTILS)) \

# SRC&OBJ
SRC				= \
				main.c \
				$(addprefix utils/, $(SRC_UTILS)) \
				$(addprefix ast/, $(SRC_AST)) \

OBJ				= ${addprefix ${OBJ_DIR}/, \
				${SRC:.c=.o}}

# **************************************************************************** #
# LIBRARIES & FRAMEWORKS


LIBFT_DIR	= libft
LIBFT_INC_DIR := $(LIBFT_DIR)
LIBFT		= ${LIBFT_DIR}/libft.a

LFLAGS		= -lreadline

# **************************************************************************** #
# INCLUDES
INC_DIR := includes
INCLUDES := -I$(INC_DIR) -I$(LIBFT_INC_DIR)

# **************************************************************************** #
# RULES


all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${CFLAGS} $^ -o ${NAME} ${LIBFT} ${LFLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

$(LIBFT):
	${MAKE} -C ${LIBFT_DIR}

clean:
	rm -rf ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} fclean

fclean: clean
	rm -f ${NAME}

re: fclean all


# **************************************************************************** #
# PHONY


.PHONY: all clean fclean re
