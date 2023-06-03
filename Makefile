SRCS = 	parsing/main.c \
		parsing/fill_types.c \
		parsing/check_syntax.c\
		parsing/set_states.c\
		parsing/files.c\
		parsing/lst_init.c\
		parsing/here_doc.c\
		parsing/here_doc_utils.c\
		parsing/splite_pipe_space.c\
		parsing/splite_pipe_space_utiles.c\
		parsing/env_link.c\
		parsing/free.c\
		parsing/lst_add.c\
		excution/builtins/echo.c \
		excution/builtins/pwd.c \
		excution/builtins/env.c \
		excution/builtins/cd.c \
		excution/builtins/cd_utils.c \
		excution/builtins/export.c \
		excution/builtins/export_utils.c \
		excution/builtins/export_utils_1.c \
		excution/builtins/export_utils_2.c \
		excution/builtins/exit.c \
		excution/builtins/utils_builtins.c \
		excution/builtins/unset.c \
		excution/execve/execution_utils.c \
		excution/execve/execution_utils_1.c \
		excution/pipes/pipes.c \
		excution/pipes/pipes_utiles_1.c \
		excution/pipes/pipes_utiles_2.c \
		parsing/files/files_1.c \
		parsing/files/files_2.c \
		parsing/files/files_3.c \
		parsing/files/files_4.c \
		parsing/files/files_5.c \
		parsing/files/files_6.c \
		parsing/files/files_7.c \
		parsing/syntax/syntax_1.c \
		parsing/syntax/syntax_2.c \
		parsing/syntax/syntax_3.c \

CFLAGS = -Wall -Wextra -Werror# -fsanitize=address
NAME = minishell
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	@stty -echoctl
	@make -sC libft/
	$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o  $(NAME) -lreadline
#-I ~/Users/hlakhal-/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/hlakhal-/goinfre/homebrew/Cellar/readline/8.2.1/lib
clean:
	@make clean -sC libft/
	$(RM) $(O_SRCS)

fclean: clean
	@make fclean -sC libft/
	$(RM) $(NAME)

re: fclean all

run :
	make
	clear
	./minishell
norm:
	@norminette

.PHONY: all clean fclean re norm
