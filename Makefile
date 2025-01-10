CC		=  cc
CFLAGS	= -Wall -Wextra -Werror -g3 -I./includes
NAME	= minishell

SRC_PATH = src/
OBJ_PATH = objs/

SRC		= minishell.c \
		  parsing/automat.c parsing/lexer_utils.c parsing/strings.c \
		  parsing/token_utils.c parsing/tokenizer.c parsing/ranger.c \
		  parsing/command_utils.c expand/expand.c env/env.c
		  

INCLUDES = ./includes
LIB_DIR = ./libft
LIBFT	= $(LIB_DIR)/libft.a
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(OBJ_PATH)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c  $< -o $@ 

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

clean:
	rm -rf $(OBJ_PATH)
	make clean -C ./libft 

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re