SRCS = 	parsing/main.c \
		parsing/fill_types.c \
		parsing/check_syntax.c\
		parsing/set_states.c\
		parsing/files.c\
		parsing/lst_init.c\
		parsing/here_doc.c\
		parsing/splite_pipe_space.c\
		parsing/env_link.c\
		exction/builtins/echo.c \
		exction/builtins/pwd.c \
		exction/builtins/env.c \
		exction/builtins/cd.c \
		exction/builtins/export.c \
		exction/execve/execution_utils.c \
		exction/pipes/pipes.c \
		# parsing/check_leaks.c\

# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address -g3
CFLAGS = -g
NAME = minishell
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	@make -sC libft/
	$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o  $(NAME) -lreadline
clean:
	$(RM) $(O_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run :
	make
	clear
	./minishell
norm:
	@norminette

.PHONY: all clean fclean re norm
