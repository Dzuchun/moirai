#include "board.h"
#include "cell.h"
#include "convert.h"
#include "game.h"
#include <debug.h>
#include <sector.h>
#include <stdint.h>
#include <stdio.h>
#include <wins.h>

// Represents all possible sector states indicating a win
//
// - 4 for possible sector offsets
// - 2 fot possible players
// - 8 for all possible win conditions
// - 3 for sector pointer size (it's 9 cells total, so they always span 3 bytes)
static int8_t wins[4][2][8][3];

// Combinations of cells that trigger a win
//
// - 3 column cells
// - 3 row cells
// - 2 diag cells
static int8_t combs[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7},
                             {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

static int8_t cell_value[2] = {(int)Cross, (int)Circle};

void init_wins() {
    int8_t cell_ind;
    for (int offset = 0; offset < 4; ++offset)
        for (int player = 0; player < 2; ++player)
            for (int combination = 0; combination < 8; ++combination) {
                wins[offset][player][combination][0] = 0;
                wins[offset][player][combination][1] = 0;
                wins[offset][player][combination][2] = 0;
                for (int cell_no = 0; cell_no < 3; ++cell_no) {
                    cell_ind = combs[combination][cell_no] - 1 + offset;
                    wins[offset][player][combination][cell_ind >> 2] |=
                        cell_value[player] << ((cell_ind & 0b11) << 1);
                }
            }
}

#ifdef DEBUG_BUILD
OffsetPlayerWinConfig *expose_wins() { return &wins[0]; }
#endif

#ifdef DEBUG_BUILD
int __intercept(SectorPtr sector, int player, int comb, int val) {
    if (val) {
        debug_report(player, "Player");
        debug_report(comb, "Compination");
        print_sector_debug(sector);
    }
    return val;
}
static int8_t *tmp;
#define _matches(sector, player, ind)                                          \
    __intercept(sector, player, ind,                                           \
                (tmp = (int8_t *)wins[sector.offset][player][ind]) &&          \
                    (tmp[0] == (tmp[0] & sector.data[0])) &&                   \
                    (tmp[1] == (tmp[1] & sector.data[1])) &&                   \
                    (tmp[2] == (tmp[2] & sector.data[2])))
#else
static int8_t *tmp;
#define _matches(sector, player, ind)                                          \
    ((tmp = (int8_t *)wins[sector.offset][player][ind]) &&                     \
     (tmp[0] == (tmp[0] & sector.data[0])) &&                                  \
     (tmp[1] == (tmp[1] & sector.data[1])) &&                                  \
     (tmp[2] == (tmp[2] & sector.data[2])))
#endif

#define _matches_outer(sector, player)                                         \
    (_matches(sector, player, 0) || _matches(sector, player, 1) ||             \
     _matches(sector, player, 2) || _matches(sector, player, 3) ||             \
     _matches(sector, player, 4) || _matches(sector, player, 5) ||             \
     _matches(sector, player, 6) || _matches(sector, player, 7))

static int _draw_offsets[4][9][2] = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}},
    {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}},
    {{0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}},
    {{0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}},
};

#define _draw(sector, ind)                                                     \
    ((sector.data[_draw_offsets[sector.offset][ind][0]] &                      \
      (0b11 << (_draw_offsets[sector.offset][ind][1] << 1))) != 0)

#define _draw_outer(sector)                                                    \
    (_draw(sector, 0) && _draw(sector, 1) && _draw(sector, 2) &&               \
     _draw(sector, 3) && _draw(sector, 4) && _draw(sector, 5) &&               \
     _draw(sector, 6) && _draw(sector, 7) && _draw(sector, 8))

WinSide get_sector_winner(SectorPtr sector) {
    // check for player wins
    if _matches_outer (sector, 0)
        return CrossPlayer;
    if _matches_outer (sector, 1)
        return CirclePlayer;
    // check for draws
    if _draw_outer (sector)
        return Draw;
    return Noone;
}

int is_legal(BoardPtr board, SectorInd sector, int cell, FILE *complain) {
    CellValue cell_value;
    int verdict = 0;
    // there are exactly 9 cells
    if (cell < 1 || cell > 9) {
        if (complain)
            fprintf(complain, "Error: cell %d is not a valid cell\n", cell);
        verdict |= 0b0001;
    }
    if (sector == SectorT) {
        if (complain)
            fprintf(complain,
                    "Error: sector T cannot be influenced directly\n");
        verdict |= 0b0010;
    }
    if (sector == InvalidSector) {
        if (complain)
            fprintf(complain, "Error: invalid sector\n");
        verdict |= 0b0100;
    }
    // can't make a move there, if this cell was already occupied
    cell_value = get_cell_board(board, sector, cell);
    if (!verdict && cell_value != Empty) {
        if (complain)
            fprintf(complain, "Error: cell (%d-%d) is already occupied\n",
                    sector, cell);
        verdict |= 0b1000;
    }
    return verdict;
}

#undef _draw_outer
#undef _draw
#undef _matches_outer
#undef _matches
