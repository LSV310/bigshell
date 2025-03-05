AR			= ar rcs
CC			= cc
CFLAGS		= -g3 -Wall -Werror -Wextra

INLCUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I../$(INLCUDES)

SRC			=	libc/ft_atoi.c				\
				libc/ft_bzero.c				\
				libc/ft_calloc.c			\
				libc/ft_isalnum.c			\
				libc/ft_isalpha.c			\
				libc/ft_isascii.c			\
				libc/ft_isdigit.c			\
				libc/ft_isprint.c			\
				libc/ft_itoa.c				\
				libc/ft_memchr.c			\
				libc/ft_memcmp.c			\
				libc/ft_memcpy.c			\
				libc/ft_memmove.c			\
				libc/ft_memset.c			\
				libc/ft_putchar_fd.c		\
				libc/ft_putendl_fd.c		\
				libc/ft_putnbr_fd.c			\
				libc/ft_putstr_fd.c			\
				libc/ft_realloc.c			\
				libc/ft_shift_elem.c		\
				libc/ft_split.c				\
				libc/ft_str_equals.c		\
				libc/ft_strchr.c			\
				libc/ft_strcmp.c			\
				libc/ft_strdup.c			\
				libc/ft_striteri.c			\
				libc/ft_strjoin.c			\
				libc/ft_strlcat.c			\
				libc/ft_strlcpy.c			\
				libc/ft_strlen.c			\
				libc/ft_strlstr.c			\
				libc/ft_strmapi.c			\
				libc/ft_strncmp.c			\
				libc/ft_strnstr.c			\
				libc/ft_strrchr.c			\
				libc/ft_strstr_tab.c		\
				libc/ft_strtrim.c			\
				libc/ft_substr.c			\
				libc/ft_tolower.c			\
				libc/ft_toupper.c			\
				libc/tab_len.c				\
				data/ft_dlst_shift.c		\
				data/ft_dlst_top.c			\
				data/ft_dlstadd_back.c		\
				data/ft_dlstadd_front.c		\
				data/ft_dlstclear.c			\
				data/ft_dlstdelone.c		\
				data/ft_dlstlast.c			\
				data/ft_dlstnew.c			\
				data/ft_dlstprint.c			\
				data/ft_dlstremove_node.c	\
				data/ft_lstadd_back.c		\
				data/ft_lstadd_front.c		\
				data/ft_lstclear.c			\
				data/ft_lstdelone.c			\
				data/ft_lstfree_content.c	\
				data/ft_lstiter.c			\
				data/ft_lstlast.c			\
				data/ft_lstmap.c			\
				data/ft_lstnew.c			\
				data/ft_lstprint.c			\
				data/ft_lstremove_node.c	\
				data/ft_lstsize.c			\
				data/ft_lstvoid_content.c	\
				data/ft_maps.c				\
				data/ft_strstr_dlst.c		\
				printf/ft_printf.c			\
				printf/ft_fprintf.c			\
				printf/ft_printf_utils.c	\
				printf/ft_printf_utils2.c	\
				readfile/get_next_line.c	\
				maths/max.c					\
				maths/min.c					\
				maths/q_rsqrt.c				\
				readline/history.c			\
				readline/keys.c				\
				readline/keys2.c			\
				readline/readline.c			\
				readline/terminal.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= libft.a


all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
