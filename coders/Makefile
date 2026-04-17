SRC_DIR := src
BUILD_DIR := .build

BASE_NAME := main error burnout parsing destroy env threads priority time routine refactor dongle debug cond compile check_end
SRC := $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(BASE_NAME)))
OBJ := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(BASE_NAME)))
DEP := $(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(BASE_NAME)))
CFLAGS = -Wall -Werror -Wextra -pthread -I.
#-fsanitize=thread

NAME = codexion

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
		$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(BUILD_DIR)/$*.d

clean:
		rm -rf $(BUILD_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

debug: fclean
	$(MAKE) CFLAGS=" -Wall -Werror -Wextra -pthread -fsanitize=thread -I."

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(DEP)