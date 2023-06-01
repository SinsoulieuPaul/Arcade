##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	Menu.cpp \
		../Core.cpp \
		../main.cpp \
		../../lib/games/Text.cpp \
		../../lib/games/Prop.cpp \
		../../lib/games/AGame.cpp \

OBJ	=	$(SRC:.cpp=.o)

NAME	=	menu.so

CPPFLAGS 	=  -std=c++20 -Wall -Wextra -Werror -fPIC

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -shared -o $(NAME) $(OBJ) $(CPPFLAGS)
	mv $(NAME) ../../../lib/$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../../lib/$(NAME)

re: fclean all
