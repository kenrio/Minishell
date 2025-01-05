# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/01/05 14:56:39 by keishii          ###   ########.fr        #
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


SRC_FILES		= main \
				utils

OBJ_FILES		= ${addprefix ${OBJ_DIR}/, \
				${SRC_FILES:=.o}}


# **************************************** #
# LIBRARIES & FRAMEWORKS


# **************************************** #
# RULES


all: ${NAME}

${NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} $^ -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all


# **************************************** #
# PHONY


.PHONY: all clean fclean re
