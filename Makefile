# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/02/01 15:24:09 by keishii          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************** #
# VARIABLES


NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

SRC_DIR			= src
OBJ_DIR			= obj


# **************************************** #
# SOURCES


SRC				= main \
				utils

OBJ				= ${addprefix ${OBJ_DIR}/, \
				${SRC:=.o}}


# **************************************** #
# LIBRARIES & FRAMEWORKS


LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a

LFLAGS		= -lreadline


# **************************************** #
# RULES


all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${CFLAGS} $^ -o ${NAME} ${LIBFT} ${LFLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

$(LIBFT):
	${MAKE} -C ${LIBFT_DIR}

clean:
	rm -rf ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} fclean

fclean: clean
	rm -f ${NAME}

re: fclean all


# **************************************** #
# PHONY


.PHONY: all clean fclean re
