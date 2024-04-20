#include "sector.h"
#include "wins.h"
#include <debug.h>
#include <stdint.h>
#include <stdio.h>
#ifdef DEBUG_BUILD

static void print_byte(int8_t b) {
    putchar(b & (1 << 7) ? '1' : '0');
    putchar(b & (1 << 6) ? '1' : '0');
    putchar(' ');
    putchar(b & (1 << 5) ? '1' : '0');
    putchar(b & (1 << 4) ? '1' : '0');
    putchar(' ');
    putchar(b & (1 << 3) ? '1' : '0');
    putchar(b & (1 << 2) ? '1' : '0');
    putchar(' ');
    putchar(b & (1 << 1) ? '1' : '0');
    putchar(b & (1 << 0) ? '1' : '0');
}

void debug_print_board(BoardPtr board) {
    for (int i = 0; i < 23; ++i) {
        printf("%2d: ", i);
        print_byte(board[i]);
        putchar('\n');
    }
}

void print_debug_wins() {
    OffsetPlayerWinConfig *wins = expose_wins();
    for (int offset = 0; offset < 4; ++offset)
        for (int player = 0; player < 2; ++player)
            for (int combination = 0; combination < 8; ++combination) {
                printf("o=%d, p=%d, c=%d: ", offset, player, combination);
                print_byte(wins[offset][player][combination][2]);
                putchar(' ');
                putchar(' ');
                print_byte(wins[offset][player][combination][1]);
                putchar(' ');
                putchar(' ');
                print_byte(wins[offset][player][combination][0]);
                putchar('\n');
            }
}

void debug_report(int val, const char *ctx) {
    printf("ctx: %s, val: %d\n", ctx, val);
}

void print_sector_debug(SectorPtr sector) {
    printf("Offset: %d; ", sector.offset);
    print_byte(sector.data[2]);
    putchar(' ');
    print_byte(sector.data[1]);
    putchar(' ');
    print_byte(sector.data[0]);
    putchar('\n');
}

#endif
