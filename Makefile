all:
	gcc -ansi -Wall -pedantic board.c con4.c game.c helpers.c player.c scoreboard.c -o con4
debug:
	gcc -ansi -Wall -pedantic board.c con4.c game.c helpers.c player.c scoreboard.c -o con4 -g
clean:
	rm con4
