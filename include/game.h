#ifndef GAME_H

#define GAME_H

#include <sector.h>
#include <stdint.h>

// First bit - if it's second player's turn
// Next 4 bits - index of the cell last move was in
typedef int8_t GameState;

enum _move_side {
    PlayerCross = 0,
    PlayerCircle = 1,
};
typedef enum _move_side MoveSide;

// Initializes state to start of the game
void initial_state(GameState *state);

// Returns side that must make next move
MoveSide get_move_side(GameState *state);

void flip_move_side(GameState *state);

// Returns sector of the next move
//
// If next sector is not determined, returns InvalidSector
SectorInd next_move_sector(GameState *state);

// Sets sector next player should move in
void set_next_move_sector(GameState *state, SectorInd sector);

#endif
