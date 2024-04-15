#include <board.h>

#include <stdio.h>
int main() {
    Board b = new_board();
    char buf[BUFSIZ];

    init_boards();
    set_cell_value(b, T_4, TIC);
    set_cell_value(b, T_3, TAC);
    set_cell_value(b, A_3, TAC);
    set_cell_value(b, A_4, TIC);

    print_board(b, buf);
    puts(buf);
    free_board(b);
}
