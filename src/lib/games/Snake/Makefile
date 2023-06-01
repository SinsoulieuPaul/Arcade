##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	Snake.cpp \
		../AGame.cpp \
		../Entity.cpp \
		../Prop.cpp \
		../../../core/Core.cpp \
		../../../core/main.cpp \
		../Text.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade_snake.so

CPPFLAGS 	=  -std=c++20 -Wall -Wextra -Werror -fPIC -g

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -shared -o $(NAME) $(OBJ) $(CPPFLAGS)
	mv $(NAME) ../../../../lib/$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../../../lib/$(NAME)

re: fclean all
