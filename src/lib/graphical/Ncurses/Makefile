##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	Ncurses.cpp \
		LibNcurses.cpp \
		../../games/Entity.cpp \
		../../games/Prop.cpp \
		../../games/Text.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade_ncurses.so

CPPFLAGS 	=  -std=c++20 -Wall -Wextra -Werror -fno-gnu-unique -fPIC

NLIB	=	-lncurses

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -shared -o $(NAME) $(OBJ) $(CPPFLAGS) $(NLIB)
	mv $(NAME) ../../../../lib/$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../../../lib/$(NAME)

re: fclean all
