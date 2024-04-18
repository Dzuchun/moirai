#ifndef BOARD_H
#define BOARD_H

#include <cell.h>
#include <stdint.h>
// Board represents state of the entire game.
//
// you can't pass around arrays in C, so most commonly we'll use board pointers
//
// Note: 24th byte of the board is unsused, and added here for purely
typedef int8_t Board[24];

// A pointer to a board
typedef int8_t *BoardPtr;

// Sets all the cells in the board to empty
void empty_board(BoardPtr board);

// Sets certain cell in the board to specified value
void set_cell_board(BoardPtr board, int sector, int cell, CellValue value);

// Gets cell of the board
CellValue get_cell_board(BoardPtr board, int sector, int cell);

// Compares two boards, returning 0 if they are equal
int8_t cmp_boards(BoardPtr board1, BoardPtr board2);

// A bundle of 8 boards
typedef int64_t Board8[24];
// A pointer to a bundle of 8 boards
typedef int64_t *Board8Ptr;

// Sets all the cells in the board bundle to empty
void empty_board8(Board8Ptr boards);

// Sets certain cell in the board bundle to specified value
void set_cell_board8(Board8Ptr boards, int sector, int cell, CellValue value);

// Gets values stored at a certain cell in 8 boards
CellValue8 get_cell_board8(Board8Ptr boards, int sector, int cell,
                           CellValuePtr values);

// Compares 8 boards, returning 0 in corresponding bit, if they are equal
int8_t eq_boards(Board8Ptr boards1, Board8Ptr boards2);

#endif
