#include "cell.h"
#include "convert.h"
#include "sector.h"
#include "wins.h"
#include <board.h>
#include <debug.h>
#include <game.h>
#include <stdint.h>

void initial_board(BoardPtr board) {
    int64_t *ptr8 = (int64_t *)board;
    ptr8[0] = 0;
    ptr8[1] = 0;
    ptr8[2] = 0;
    int8_t *ptr = (int8_t *)board;
    initial_state(ptr + 23);
}

#define cell_index(sector, cell) (((int)sector) * 9) + (cell - 1)

void set_cell_board(BoardPtr board, SectorInd sector, int cell,
                    CellValue value) {
    int ci = cell_index(sector, cell); // cell index, 0-89
    // update last move, if needed
    if (sector != InvalidSector && sector != SectorT) {
        SectorInd next_sector = cell_to_sector(cell);
        GameState *state = get_game_state(board);
        if (get_sector_winner(get_sector_board(board, next_sector)) == Noone)
            // next sector's local winner is not yet determined
            set_next_move_sector(state, next_sector);
        else
            // next sector's local winner was determined, and noone can move
            // there
            set_next_move_sector(state, InvalidSector);
    }
    int bi = ci >> 2;              // byte index, 0-22
    ci &= 0b11;                    // cell index inside a byte, 0-3
    ci <<= 1;                      // cell index inside a byte, 0,2,4,6
    int8_t cell_mask = 0b11 << ci; // cell mask
    ci = ((int)value) << ci;       // value bytes at correct position
    // now we need to zero-out these bytes the board
    board[bi] &= (~cell_mask);
    // and finally set them
    board[bi] |= ci;
}

CellValue get_cell_board(BoardPtr board, SectorInd sector, int cell) {
    int ci = cell_index(sector, cell); // cell index, 0-89
    int bi = ci >> 2;                  // byte index, 0-22
    ci &= 0b11;                        // cell offset, 0-3
    ci <<= 1;                          // cell offset 0,2,4,6
    int cv = 0b11 << ci;               // cell value mask
    cv &= board[bi];                   // cell value, shifted
    cv >>= ci;                         // cell value, unshifted
    return (CellValue)cv;
}

SectorPtr get_sector_board(BoardPtr board, SectorInd sector) {
    SectorPtr res;
    int ci = cell_index(sector, 1); // index of the first cell in the sector
    int bi = ci >> 2;               // first byte mentioned in the sector
    res.data = board + bi;
    res.offset = ci & 0b11; // offset is just ci % 4
    return res;
}

GameState *get_game_state(BoardPtr board) { return (GameState *)board + 23; }
