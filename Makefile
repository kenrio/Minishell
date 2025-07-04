# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 12:15:09 by keishii           #+#    #+#              #
#    Updated: 2025/04/27 19:53:34 by tishihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES


NAME			:= minishell

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

SRC_DIR			:= src
OBJ_DIR			:= obj


# **************************************************************************** #
# SOURCES


SRC_LEXER		:= \
				lexer.c \
				count_tokens.c \
				tokenize.c \
				add_token_to_array.c \
				assign_token_type.c \
				free_token_array.c \
				lexer_utils.c \

SRC_EXPANTION	:= \
				elements.c \
				elements_heredoc.c \
				expand_doller.c \
        
SRC_DEBUG		:= \
				debug_lexer.c \
				check_expantion.c \
				debug_parser.c \

SRC_PARSER		:= \
				parser.c \
				make_ast.c \
				parse_pipe.c \
				make_pipe_node.c \
				parse_cmd.c \
				make_cmd_node.c \
				add_args.c \
				add_redirect.c \
				free_ast.c \
				parser_utils.c \
				syntax_error.c \
				copy_ast.c \

SRC_BUILTIN		:= \
				execute_builtin.c \
				execute_echo.c \
				execute_cd.c \
				execute_pwd.c \
				execute_export.c \
				execute_unset.c \
				execute_env.c \
				execute_exit.c \

SRC_SIGNAL		:= \
				signal_handler.c \
				signal_set_handler.c \

SRC_UTILS		:= \
				heredoc.c \
				pids.c \
				redirect.c \
				boundary_split.c \
				join_all_split.c \
				ft_strcmp.c \
				get_path.c \
				strrmchr.c \
				utils.c \
				copy_str_array.c \
				free_str_array.c \

SRC_AST			:= \
				exec_ast.c \
				exec_ast_pipe.c \
				exec_ast_cmd.c \
				exec_child_component.c \

SRC_ENVP		:= \
				envl.c \
				handle_envl.c \
				make_envp.c \

# SRC&OBJ
SRC				:= \
				main.c \
				$(addprefix ast/, $(SRC_AST)) \
        		$(addprefix lexer/, $(SRC_LEXER)) \
        		$(addprefix expantion/, $(SRC_EXPANTION)) \
            	$(addprefix debug/, $(SRC_DEBUG)) \
				$(addprefix utils/, $(SRC_UTILS)) \
        		$(addprefix parser/, $(SRC_PARSER)) \
				$(addprefix signal/, $(SRC_SIGNAL)) \
        		$(addprefix envp/, $(SRC_ENVP)) \
        		$(addprefix builtin/, $(SRC_BUILTIN)) \

OBJ				:= ${addprefix ${OBJ_DIR}/, \
				${SRC:.c=.o}}


# **************************************************************************** #
# LIBRARIES & FRAMEWORKS


LIBFT_DIR		:= libft
LIBFT_INC_DIR	:= $(LIBFT_DIR)
LIBFT			:= ${LIBFT_DIR}/libft.a

UNAME 			:= $(shell uname)

LFLAGS			:= -lreadline

ifeq ($(UNAME), Darwin)
	RL_DIR			:= /opt/homebrew/opt/readline
	RL_LIB_DIR		:= $(RL_DIR)/lib
	LFLAGS			+= -L$(RL_LIB_DIR)
endif


# **************************************************************************** #
# INCLUDES


INC_DIR		:= includes
INCLUDES	:= -I$(INC_DIR) -I$(LIBFT_INC_DIR)
ifeq ($(UNAME), Darwin)
	RL_INC_DIR		:= $(RL_DIR)/include
	INCLUDES		+= -I$(RL_INC_DIR)
endif


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
