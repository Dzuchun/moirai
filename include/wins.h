#ifndef WINS_H
#define WINS_H

#include <board.h>
#include <cell.h>
#include <sector.h>
#include <stdint.h>
#include <stdio.h>

enum _win_side {
    Noone = Empty,
    CrossPlayer = Cross,
    CirclePlayer = Circle,
    Draw = 0b11, // this represents invalid states too
};
// A player that had won in a sector
typedef enum _win_side WinSide;

// Any win configuration spans 3 bytes
typedef int8_t WinConfig[3];
// There are exactly win configurations for each player
typedef WinConfig PlayerWinConfig[8];
// There are 2 players
typedef PlayerWinConfig OffsetPlayerWinConfig[2];
// There are 4 offsets
typedef OffsetPlayerWinConfig AllWins[4];

// Performs wins initialization.
//
// Must be called before any other function
void init_wins();

#ifdef DEBUG_BUILD
// Exposes private wins array, for debug purposes
//
// This definition does not exists, if DEBUG_BUILD-thins is not defined at
// compile-time
OffsetPlayerWinConfig *expose_wins();
#endif

// Determines winner of the sector, if there are any
WinSide get_sector_winner(SectorPtr sector);

// Players that had won in 8 sectors
typedef int16_t WinSide8;

// Determines winners of supplid sectors and assigns them to supplied array.
// Preasumed to have at least count/8 memory
void get_sectors_winners(SectorPtr *sectors, WinSide8 *winners, int count);

// Determines winners of a given board and assigns them to supplied pointers.
//
// Since there are 10 sectors of the board, there are 10 winnars total
void get_board_winners(BoardPtr board, WinSide8 *first_eight,
                       WinSide8 *last_two);

// Determines winners of the 8 boards and writes them to supplied array
//
// There's expected to be space for at least 10 Winside8 objects, and each
// object will represent winners of a sertain sector from supplied 8 boards
void get_boards_winners(Board8Ptr boards, WinSide8 *winners);

// Determines if proposed move is legal.
//
// 0 means move is ok
//
// You may optionally speficy a file to complain into
int is_legal(BoardPtr board, SectorInd sector, int cell, FILE *complain);

#endif
