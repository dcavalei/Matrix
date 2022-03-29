SRC		= $(shell find src -type f -name "*.cpp")
DEPS	= $(shell find inc -type f -name "*.hpp") Makefile
OBJ		= $(SRC:src/%.cpp=obj/%.o)
CC		= clang++
CFLAGS	= -Wall -Wextra -std=c++17 -Iinc -g
NAME	= Matrix

all: $(NAME)

obj/%.o:	src/%.cpp $(DEPS)
	@mkdir -pv $(dir $@)
	@$(CC) $(CFLAGS) -Iinc -c $< -o $@

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:	all
	@./$(NAME)

runv:	all
	@valgrind ./$(NAME)

clean:
	@rm -vrf obj

fclean:	clean
	@rm -vrf $(NAME)

re:	fclean all

.PHONY:	all run runv clean fclean re
