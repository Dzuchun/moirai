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
typedef int (*FixedSectorBrain)(BoardPtr, SectorInd, int *);
// A function player uses to determine their next move in case they can make it
// in any sector
//
// Must return NON-ZERO, if player is willing to keep playing
//
// In case 0 was returned, player is considered surrendering
typedef int (*AnySectorBrain)(BoardPtr, SectorInd *, int *);

struct _player_brain {
    FixedSectorBrain fixed;
    AnySectorBrain any;
};
// A simple struct containing pointers to player's brain
typedef struct _player_brain PlayerBrain;

#endif
