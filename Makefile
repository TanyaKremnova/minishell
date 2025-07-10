RED = \033[0;31m
GREEN = \033[1;32m
YELLOW = \033[0;33m
RESET = \033[0m

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
RNFLAGS = -lreadline -lncurses 

# L
# CFLAGS = -Wall -Wextra -Werror -g3 -I/opt/homebrew/opt/readline/include -I./include
# RNFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline -lncurses

# T
# CFLAGS = -Wall -Wextra -Werror -g3 -I/usr/local/opt/readline/include -I./include
# RNFLAGS = -L/usr/local/opt/readline/lib -lreadline -lncurses

HEADERS = -I./include

LEXER_DIR = src/lexer
AST_DIR = src/ast
EXEC_DIR = src/exec
EXEC_BUILD_IN_DIR = src/exec/exec_build_in
SIGNAL_DIR = src/signals
OBJ_DIR = obj

SRC = src/main.c \
	src/main_utils.c \
	src/minishell.c \
	src/minishell_utils.c \
	$(SIGNAL_DIR)/signals.c \
	$(SIGNAL_DIR)/signal_message.c \
	$(LEXER_DIR)/token.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/whatever_tokens.c \
	$(LEXER_DIR)/quotes_token.c \
	$(LEXER_DIR)/redirect_tokens.c \
	$(LEXER_DIR)/lexer_util.c \
	$(LEXER_DIR)/analyze_syntax.c \
	$(AST_DIR)/ast.c \
	$(AST_DIR)/ast_malloc.c \
	$(AST_DIR)/ast_util.c \
	$(AST_DIR)/free_ast.c \
	$(EXEC_DIR)/preprocess_heredoc.c \
	$(EXEC_DIR)/preprocess_heredoc_utils.c \
	$(EXEC_DIR)/exec.c \
	$(EXEC_DIR)/expand_args.c \
	$(EXEC_DIR)/expand_args_utils.c \
	$(EXEC_DIR)/handle_pipe.c \
	$(EXEC_DIR)/handle_cmd.c \
	$(EXEC_DIR)/handle_cmd_util.c \
	$(EXEC_DIR)/handle_redirections.c \
	$(EXEC_DIR)/find_command_path.c \
	$(EXEC_DIR)/handle_buildin.c \
	$(EXEC_DIR)/exec_util.c \
	$(EXEC_BUILD_IN_DIR)/execute_cd.c \
	$(EXEC_BUILD_IN_DIR)/execute_cd_util.c \
	$(EXEC_BUILD_IN_DIR)/execute_echo.c \
	$(EXEC_BUILD_IN_DIR)/execute_echo_utils.c \
	$(EXEC_BUILD_IN_DIR)/execute_env.c \
	$(EXEC_BUILD_IN_DIR)/execute_exit.c \
	$(EXEC_BUILD_IN_DIR)/execute_export.c \
	$(EXEC_BUILD_IN_DIR)/execute_export_util0.c \
	$(EXEC_BUILD_IN_DIR)/execute_export_util1.c \
	$(EXEC_BUILD_IN_DIR)/execute_export_util2.c \
	$(EXEC_BUILD_IN_DIR)/execute_pwd.c \
	$(EXEC_BUILD_IN_DIR)/execute_unset.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(HEADERS) $(LIBFT) $(RNFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ Project $(NAME) created.$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_PATH)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(YELLOW)✓ Project $(NAME) and all files cleaned.$(RESET)"

re: fclean all

valgrind_supp: re
	@echo "$(YELLOW)🔍 Running Valgrind with suppression file...$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=local.supp -s ./minishell

.PHONY: all clean fclean re