

main:
	clang -I ./include ./src/board.c ./src/main.c -o main

main-dbg:
	clang -g -I ./include ./src/board.c ./src/main.c -o main


force-main: clean main

force-main-dbg: clean main-dbg

clean:
	rm main
