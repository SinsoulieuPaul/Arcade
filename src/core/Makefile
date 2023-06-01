##
## EPITECH PROJECT, 2023
## B-OOP-400-LIL-4-1-arcade-bauchart.loic
## File description:
## Makefile
##

CPP = g++
CPPFLAGS 	= -std=c++20 -Wall -Wextra -Werror -fPIC

SRC =	Core.cpp \
		main.cpp \
		../lib/games/AGame.cpp \
		../lib/games/Prop.cpp \
		../lib/games/Entity.cpp \
		../lib/games/Text.cpp \

OBJ = $(SRC:.cpp=.o)
EXEC = arcade

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ)
	mv ${EXEC} ../../${EXEC}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../$(EXEC)
	rm -rf ../../score.txt

re: fclean all