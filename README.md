# Connect 4 CLI Game

*This was a university submission from 2015*

I was asked to create a CLI version of Connect 4 written entirely in C.

Startup code was supplied with only data structures defined - this code utilises and expands thes structures and provides an implementation of the classic Connect 4 game.



### Usage

A `Makefile` has been provided:

```makefile
all:
	gcc -ansi -Wall -pedantic board.c con4.c game.c helpers.c player.c scoreboard.c -o con4
debug:
	gcc -ansi -Wall -pedantic board.c con4.c game.c helpers.c player.c scoreboard.c -o con4 -g
clean:
	rm con4
```

Simply run `make` in the project directory, and run the `con4` binary.
