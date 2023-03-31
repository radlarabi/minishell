SRCS = 	parsing/main.c \

# CFLAGS = 
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