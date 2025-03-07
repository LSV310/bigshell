CC			= cc
CFLAGS		= -g3 #-Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			=	arena/arena.c				\
				arena/ft_arena.c			\
				ast/here_doc.c				\
				ast/parse_cmd.c				\
				builtins/cd.c				\
				builtins/echo.c				\
				builtins/env.c				\
				builtins/exit.c				\
				builtins/export.c			\
				builtins/pwd.c				\
				builtins/unset.c			\
				env/create_env.c			\
				env/env_utils.c				\
				lexer/ft_lexer.c			\
				lexer/is_utils.c			\
				lexer/token_expand.c		\
				lexer/token_make_utils.c	\
				lexer/token_make.c			\
				lexer/token_utils.c			\
				pipex/pipex.c				\
				pipex/search_cmd.c			\
				signals/signals.c			\
				utils/wildcards.c			\
				main.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@cp $(NAME) ~/.local/bin/

$(LIBFT):
	make -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
