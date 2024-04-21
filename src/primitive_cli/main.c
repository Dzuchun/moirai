#include <board.h>
#include <cell.h>
#include <convert.h>
#include <debug.h>
#include <driver.h>
#include <game.h>
#include <io.h>
#include <player.h>
#include <player/primitive_io.h>
#include <sector.h>
#include <stdint.h>
#include <stdio.h>
#include <wins.h>

extern FILE *playerin, *playerout;

static void greet_winner(BoardPtr board, WinSide winner);

int main() {
    Board b;
    BoardPtr bp = (int8_t *)&b;
    WinSide global_winner = Noone;
    playerin = stdin;
    playerout = stdout;
    init_wins();
    initial_board(bp);
    global_winner =
        drive_to_end(bp, primitive_io_brain(), primitive_io_brain(), stderr);
    greet_winner(bp, global_winner);
}

static char buf[BUFSIZ];

void greet_winner(BoardPtr board, WinSide side) {
    char *bp = buf;
    display_board(&bp, board);
    switch (side) {
    case Cross:
    case Circle:
        dstcat(bp, "\nThe winner is... ");
        display_win_side(&bp, side);
        dstcat(bp, "!\nGrats!\n");
        break;
    case Draw:
        dstcat(bp, "\nIt's a DRAW! What a match!\n");
        break;
    case Noone:
        fprintf(stderr, "\tThats a serious error. Investigate.\n");
    }
    puts(buf);
}
