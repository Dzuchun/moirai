#ifndef IO_H
#define IO_H

#include <board.h>
#include <cell.h>
#include <game.h>
#include <sector.h>
#include <wins.h>

// This header defines operation used to parse and display in-game objects as
// text

void display_win_side(char **dst, WinSide side);

void display_move_side(char **dst, MoveSide side);

void display_game_state(char **dst, GameState *state);

void display_cell_value(char **dst, CellValue value);

// Displays grid the game takes on
void display_game_grid(char **dst, BoardPtr board);

// Displays grid of the game AND info on current state
void display_board(char **dst, BoardPtr board);

void display_sector_ind(char **dst, SectorInd sector);

// Parses sector index from src. Returns negative value if parsing failed
int parse_sector_ind(char **src, SectorInd *sector);

#define dstcat(dst, text)                                                      \
    {                                                                          \
        strcat(dst, text);                                                     \
        dst += sizeof(text) - 1;                                               \
    }

#endif
