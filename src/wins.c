#include "cell.h"
#include "convert.h"
#include "game.h"
#include <sector.h>
#include <stdint.h>
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
    for (int offset = 0; offset < 3; ++offset)
        for (int player = 0; player < 2; ++player)
            for (int combination = 0; combination < 8; ++combination) {
                wins[offset][player][combination][0] = 0;
                wins[offset][player][combination][1] = 0;
                wins[offset][player][combination][2] = 0;
                for (int cell_no = 0; cell_no < 3; ++cell_no) {
                    cell_ind = combs[combination][cell_no] - 1 + offset;
                    wins[offset][player][combination][cell_ind >> 2] |=
                        cell_value[player] << (cell_ind & 0b11);
                }
            }
}

static int8_t *tmp;
#define _matches(sector, player, ind)                                          \
    ((tmp = (int8_t *)wins[sector.offset][player][ind]) &&                     \
     tmp[0] == (tmp[0] & sector.data[0])) &&                                   \
        (tmp[1] == (tmp[1] & sector.data[1])) &&                               \
        (tmp[2] == (tmp[2] & sector.data[2]))
#define _matches_outer(sector, player)                                         \
    _matches(sector, player, 0) || _matches(sector, player, 1) ||              \
        _matches(sector, player, 2) || _matches(sector, player, 3) ||          \
        _matches(sector, player, 4) || _matches(sector, player, 5) ||          \
        _matches(sector, player, 6) || _matches(sector, player, 7)

WinSide get_sector_winner(SectorPtr sector) {
    if (_matches_outer(sector, 0))
        return CrossPlayer;
    if (_matches_outer(sector, 1))
        return CirclePlayer;
    return Noone;
}

#undef _matches_outer
#undef _matches
