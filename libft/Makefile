# srcs

SRCS =
SRCS += ft_isalpha.c
SRCS += ft_isdigit.c
SRCS += ft_isalnum.c
SRCS += ft_isascii.c
SRCS += ft_isprint.c
SRCS += ft_strlen.c
SRCS += ft_memset.c
SRCS += ft_bzero.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_strlcpy.c
SRCS += ft_strlcat.c
SRCS += ft_toupper.c
SRCS += ft_tolower.c
SRCS += ft_strchr.c
SRCS += ft_strrchr.c
SRCS += ft_strncmp.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_strnstr.c
SRCS += ft_atoi.c
SRCS += ft_calloc.c
SRCS += ft_strdup.c
SRCS += ft_substr.c
SRCS += ft_strjoin.c
SRCS += ft_strtrim.c
SRCS += ft_split.c
SRCS += ft_split_boundary.c
SRCS += ft_split_all_join.c
SRCS += ft_split_destroy.c
SRCS += ft_itoa.c
SRCS += ft_strmapi.c
SRCS += ft_striteri.c
SRCS += ft_putchar_fd.c
SRCS += ft_putstr_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_fd.c

SRCS_BONUS =
SRCS_BONUS += ft_lstnew.c
SRCS_BONUS += ft_lstadd_front.c
SRCS_BONUS += ft_lstsize.c
SRCS_BONUS += ft_lstlast.c
SRCS_BONUS += ft_lstadd_back.c
SRCS_BONUS += ft_lstdelone.c
SRCS_BONUS += ft_lstclear.c
SRCS_BONUS += ft_lstiter.c
SRCS_BONUS += ft_lstmap.c

OBJS := $(SRCS:%.c=%.o)
OBJS_BONUS := $(SRCS_BONUS:%.c=%.o)

# Name of the library
NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
DFLAGS := -g3 -fsanitize=address

ifdef DEBUG_MODE
	CFLAGS := DFLAGS
endif

ifdef ADD_BONUS
	OBJS += $(OBJS_BONUS)
endif

# Default targets
.PHONY:all
all: $(NAME)

# target
%.o:%.c	
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

.PHONY:bonus
bonus:
	@make ADD_BONUS=1

.PHONY:debug
debug:
	@make DEBUG_MODE=1
	$(CC) $(DFLAGS) main.c $(OBJS) -o libft.out

.PHONY:clean
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

.PHONY:fclean
fclean:clean
	rm -f $(NAME)

.PHONY:re
re:fclean all
