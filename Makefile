NAME = minishell

C_FILES =	main.c str_replace.c store_env.c env_list_utils.c env_list_utils2.c input.c parse_input.c \
			replace_var_names.c split_split.c pipe_split.c exec.c child.c \
			split_split_utils.c pipe_utils.c remove_surrounding_quotes.c \
			builtin/echo.c builtin/builtin.c builtin/export.c builtin/ft_pwd.c builtin/ft_cd.c builtin/ft_unset.c \
			builtin/ft_exit.c builtin/ft_export_append.c builtin/handle_overflow.c \
			redirections.c redirections_utils.c heredoc.c heredoc_utils.c \
			apply_redirection.c sig_heredoc.c

SRCS = $(addprefix srcs/,$(C_FILES))
OBJS = $(addprefix $(OBJS_DIR),$(C_FILES:.c=.o))
OBJS_DIR = ./objs/
DEPS = $(OBJS:.o=.d)

RED=\033[0;31m
ROSE=\033[0;95m
GREEN=\033[0;32m
NC=\033[0m
YELLOW=\033[0;33m
CYAN=\033[1;34m


CFLAGS = -Wall -Wextra -Werror -I includes/ -g3

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Creating libft...✅$(NC)"
	@make -C libft/ > /dev/null 2>&1
	@echo "$(YELLOW)Creating michelle...✅$(NC)"
	@cc $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lreadline
	@echo "$(CYAN)Done 🔥\n$(NC)"


$(OBJS_DIR)%.o: srcs/%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtin
	@cc $(CFLAGS) -MMD -c $< -o $@

clean:
	@echo "$(RED)Deleting objects files...✅$(NC)"
	@make -C libft/ clean
	@rm -f $(OBJS) $(DEPS)
	@echo "$(CYAN)Done 🔥\n$(NC)"



fclean: clean
	@echo "$(RED)Deleting michelle file...✅$(NC)"
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@echo "$(CYAN)Done 🔥\n$(NC)"

re: fclean all
-include $(DEPS)

.PHONY: all clean fclean re
