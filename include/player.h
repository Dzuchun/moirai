#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "sector.h"

// A function player uses to determine their next move in case sector move is
// performed in is pre-defined
//
// Must return NON-ZERO, if player is willing to keep playing
//
// In case 0 was returned, player is considered surrendering
//
// Last argument is player's state
typedef int (*FixedSectorBrain)(BoardPtr, SectorInd, int *, void *);

// A function player uses to determine their next move in case they can make it
// in any sector
//
// Must return NON-ZERO, if player is willing to keep playing
//
// In case 0 was returned, player is considered surrendering
//
// Last argument is player's state
typedef int (*AnySectorBrain)(BoardPtr, SectorInd *, int *, void *);

// A function player uses to free any resources allocated for it's state
typedef void (*PlayerDestructor)(void *);

struct _player_brain {
    FixedSectorBrain fixed;
    AnySectorBrain any;
    // Any state player needs to handle
    void *state;
    // A function to be called to dispose of a player
    PlayerDestructor distructor;
};
// A simple struct containing pointers to player's brain
typedef struct _player_brain PlayerBrain;

// Disposes of the player's brain.
//
// Player must not be used after that.
void dispose(PlayerBrain *player);

int player_get_any_sector(PlayerBrain *player, BoardPtr board,
                          SectorInd *sector, int *cell);

int player_get_fixed_sector(PlayerBrain *player, BoardPtr board,
                            SectorInd sector, int *cell);

#endif
