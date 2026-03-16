SRC = main.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -I.

DEP = $(OBJ:.o=.d)

NAME = codexion

OBJ = $(SRC:.c=.o)

.PHONY: all re fclean clean

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean: 
		rm -rf $(OBJ) $(DEP)

fclean: clean
		rm -f $(NAME)

re: fclean all

-include $(DEP)