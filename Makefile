##
## VALKA PROJECT, 2025
## Makefile
## File description:
## Valka C Makefile
##

GREEN		:= \033[0;32m
YELLOW		:= \033[0;33m
RED    		:= \033[0;31m
RESET		:= \033[0m

PREFIX		:= [VALKA]

SRC_DIR		:= src
BUILD_PATH	:= build/
OBJ_DIR		:= $(BUILD_PATH)
NAME		:= valkac
COMPIL		:= gcc
CFLAGS		:= -Wall -Wextra -Werror -Wpedantic -I./include/ -g
LIBS		:= -L./build/lib -lmemory

SRC		:= $(shell find $(SRC_DIR) -name "*.c")
OBJ		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(BUILD_PATH)
	@printf "$(GREEN)$(PREFIX) Starting compilation libraries...$(RESET)\n"
	@make -C ./lib/memory_lib/
	@printf "$(GREEN)$(PREFIX) Starting linking...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@mv $(NAME) $(BUILD_PATH)
	@cp $(BUILD_PATH)$(NAME) .
	@printf "$(GREEN)$(PREFIX) BUILD done!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)$(PREFIX) Compiling $<...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)$(PREFIX) Compiled $< successfully!$(RESET)\n"

clean:
	@make clean -C ./lib/memory_lib/
	@if [ -d $(BUILD_PATH) ]; then \
	    printf "$(RED)$(PREFIX) Cleaning object files...$(RESET)\n"; \
	    find $(BUILD_PATH) -type f -name '*.o' -delete; \
	fi

fclean: clean
	@printf "$(RED)$(PREFIX) Cleaning build folder...$(RESET)\n"
	@rm -rf $(BUILD_PATH)
	@rm -f $(NAME) a.out out.ll

re: fclean all

.PHONY: all clean fclean re
