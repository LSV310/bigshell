CC			= cc
CFLAGS		= -Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			=	arena/arena.c				\
				arena/ft_arena.c			\
				ast/ast.c					\
				ast/exec_ast.c				\
				ast/here_doc.c				\
				ast/itoarena.c				\
				ast/pipeline.c				\
				builtins/cd.c				\
				builtins/echo.c				\
				builtins/env.c				\
				builtins/exit.c				\
				builtins/export.c			\
				builtins/pwd.c				\
				builtins/unset.c			\
				env/create_env.c			\
				env/env_exp.c				\
				env/env_utils.c				\
				env/fill_token.c			\
				env/tk_to_tks.c				\
				env/token_expand.c			\
				env/token_expand2.c			\
				lexer/check_tks.c			\
				lexer/ft_lexer.c			\
				lexer/is_utils.c			\
				lexer/token_make_utils.c	\
				lexer/token_make.c			\
				lexer/token_utils.c			\
				parser/cmd_arr.c			\
				parser/parse_cmd.c			\
				pipex/pipex.c				\
				pipex/exec_builtins.c		\
				pipex/search_cmd.c			\
				pipex/wait_childs.c			\
				signals/signals.c			\
				utils/builtins_utils.c		\
				utils/get_prompt.c			\
				utils/wildcards_utils.c		\
				utils/wildcards.c			\
				main.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

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
