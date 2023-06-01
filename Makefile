##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

all:
	make -C src/lib/games
	make -C src/lib/graphical
	make -C src/core
	make -C src/core/Menu
clean:
	make -C src/lib/games clean
	# make -C src/lib/graphical clean
	make -C src/core clean

games:
	make -C src/lib/games

graphicals:
	make -C src/lib/graphical

core:
	make -C src/core
	make -C src/core/Menu

fclean:
	make -C src/lib/games fclean
	make -C src/lib/graphical fclean
	make -C src/core fclean
	make -C src/core/Menu fclean
	rm -rf score.txt

re: fclean all
