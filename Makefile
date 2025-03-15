# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/03/15 15:22:12 by keishii          ###   ########.fr        #
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


SRC_LEXER		= \
				lexer.c \
				count_tokens.c \
				tokenize.c \
				add_token_to_array.c \
				assign_token_type.c \
				free_token_array.c \
				lexer_utils.c \

SRC_UTILS		= \
				utils.c \
				ft_strcmp.c \

SRC_AST			= \
				exec_ast.c \

SRC_DEBUG		= \
				debug_lexer.c \

SRC_PARSER		= \
				parser.c \

# SRC&OBJ
SRC				= \
				main.c \
				$(addprefix utils/, $(SRC_UTILS)) \
				$(addprefix ast/, $(SRC_AST)) \
        		$(addprefix lexer/, $(SRC_LEXER)) \
				$(addprefix parser/, $(SRC_PARSER)) \
        

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
