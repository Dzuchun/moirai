#ifndef BOARD_H
#define BOARD_H

#include <cell.h>
#include <game.h>
#include <sector.h>
#include <stdint.h>
// Board represents state of the entire game.
//
// you can't pass around arrays in C, so most commonly we'll use board pointers
//
// Note: 24th byte of the board is used for storing game state
typedef int8_t Board[24];

// A pointer to a board
typedef int8_t *BoardPtr;

// Sets board to it's initial state
void initial_board(BoardPtr board);

// Sets certain cell in the board to specified value
void set_cell_board(BoardPtr board, SectorInd sector, int cell,
                    CellValue value);

// Gets cell of the board
CellValue get_cell_board(BoardPtr board, SectorInd sector, int cell);

// Gets sector of the board
SectorPtr get_sector_board(BoardPtr board, SectorInd sector);

// Gets current game state
GameState *get_game_state(BoardPtr board);

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
