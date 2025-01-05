# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/01/05 12:31:56 by keishii          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************** #
# VARIABLES


NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror


# **************************************** #
# SOURCES


SRC_FILES		= ${addprefix src/, \
				main }	

OBJ_FILES		= ${addsuffix .o, ${SRC_FILES}}


# **************************************** #
# LIBRARIES & FRAMEWORKS


# **************************************** #
# RULES


all: ${NAME}

${NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} $^ -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

clean:
	rm -f ${OBJ_FILES}

fclean: clean
	rm -f ${NAME}

re: fclean all


# **************************************** #
# PHONY


.PHONY: all clean fclean re

