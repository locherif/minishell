CC		=  cc
CFLAGS	= -Wall -Wextra -Werror -g3 -I./includes
NAME	= minishell

SRC_PATH = src/
OBJ_PATH = objs/

SRC		= minishell.c \
		  parsing/automat.c parsing/lexer_utils.c parsing/strings.c \
		  parsing/token_utils.c parsing/tokenizer.c parsing/ranger.c \
		  lib/ft_calloc.c parsing/command_utils.c expand/expand.c
		  



SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(OBJ_PATH)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re