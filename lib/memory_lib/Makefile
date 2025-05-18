##
## VALKA PROJECT, 2025
## Makefile
## File description:
## MEMORY MAKEFILE
##

RED    		:= \033[0;31m
RESET		:= \033[0m

PREFIX		:= [VALKA MEMORY]

SRC		:=	$(shell find src -name "*.c")
OBJ_SRC		:=	$(SRC:.c=.o)
NAME		:=	libmemory.a

CC		:=	cc
CFLAGS		:=	-Wall -Wextra -g -I./include/

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@ar rcs $(NAME) $(OBJ_SRC)
	@mkdir -p ../../build/lib/
	@mv $(NAME) ../../build/lib/

%.o: %.c
	@printf "$(RED)$(PREFIX) Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_SRC)

fclean: clean
	@rm -f ../../build/lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
