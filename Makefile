SRC = main.c parsing.c env.c threads.c time.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g3 -I.
#-fsanitize=thread
DEP = $(OBJ:.o=.d)

NAME = codexion

OBJ = $(SRC:.c=.o)

.PHONY: all re clean fclean 

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

%.o:%.c
		$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
		rm -rf $(OBJ) $(DEP)

fclean: clean
		rm -rf $(NAME)

re: fclean all

-include $(DEP)