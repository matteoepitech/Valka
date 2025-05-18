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

SRC		:= $(shell find src -name "*.c")
OBJ		:= $(SRC:.c=.o)
NAME		:= valkac
COMPIL		:= gcc
CFLAGS		:= -Wall -Wextra -Werror -Wpedantic -I./include/ -g
LIBS		:= -L./build/lib -lmemory

BUILD_PATH	:= build/

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p $(BUILD_PATH)
	@printf "$(GREEN)$(PREFIX) Starting compilation libraries...$(RESET)\n"
	@make -C ./lib/memory_lib/
	@printf "$(GREEN)$(PREFIX) Starting compilation...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@mv $(OBJ) $(BUILD_PATH)
	@mv $(NAME) $(BUILD_PATH)
	@cp $(BUILD_PATH)$(NAME) .
	@printf "$(GREEN)$(PREFIX) Compilation done!$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)$(PREFIX) Compiling $<...$(RESET)\n"
	@$(COMPIL) $(CFLAGS) -c $< -o $@ $(LIBS)
	@printf "$(GREEN)$(PREFIX) Compiled $< successfully!$(RESET)\n"

clean:
	@make clean -C ./lib/memory_lib/
	@printf "$(RED)$(PREFIX) Cleaning object files...$(RESET)\n"
	@find $(BUILD_PATH) -type f -name '*.o' -delete

fclean: clean
	@make fclean -C ./lib/memory_lib/
	@printf "$(RED)$(PREFIX) Cleaning build folder...$(RESET)\n"
	@rm -rf $(BUILD_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
