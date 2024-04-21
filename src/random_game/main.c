#include "io.h"
#include "player/random.h"
#include "wins.h"
#include <board.h>
#include <driver.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void seed_random();

void greet_winner(BoardPtr, WinSide);

int main() {
    Board b;
    BoardPtr bp = (int8_t *)&b;
    WinSide global_winner;
    // actually seed the random!
    seed_random();
    init_wins();
    initial_board(bp);
    global_winner =
        drive_to_end(bp, bot_random_brain(), bot_random_brain(), NULL);
    greet_winner(bp, global_winner);
}

void seed_random() {
    int seed;
    FILE *rand = fopen("/dev/random", "r");
    fread_unlocked(&seed, sizeof(seed), 1, rand);
    fclose(rand);
    srand(seed);
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
