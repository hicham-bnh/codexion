SRC = main.c burnout.c parsing.c env.c threads.c priority.c time.c routine.c refactor.c dongle.c debug.c cond.c compile.c check_end.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread  -I.
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

debug: fclean
	$(MAKE) CFLAGS=" -Wall -Werror -Wextra -pthread -fsanitize=thread -I."

-include $(DEP)