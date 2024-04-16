

main:
	clang -I ./include src/*.c src/main/main.c -o main

main-dbg:
	clang -g -I ./include src/*.c src/main/main.c -o main

test:
	clang -g -I ./include src/*.c src/tests/cell_value.c -o test_cell_value
	clang -g -I ./include src/*.c src/tests/parse_cell.c -o test_parse_cell
	./test_cell_value || ./test_parse_cell

re-main: clean main

re-main-dbg: clean main-dbg

clean:
	rm -f main test_cell_value
