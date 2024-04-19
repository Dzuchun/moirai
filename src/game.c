#include "convert.h"
#include "sector.h"
#include "wins.h"
#include <game.h>

inline void initial_state(GameState *state) {
    *state = 0b00000111;
    //         0
    //         ^ - first move is if cross player
    //          0000
    //          ^^^^ - there was no last move to determine next cell
}

inline MoveSide get_move_side(GameState *state) {
    switch (*state & 0b10000000) {
    case 0:
        return PlayerCross;
    default:
        return PlayerCircle;
    }
}

inline void flip_move_side(GameState *state) { *state ^= 0b10000000; }

inline SectorInd next_move_sector(GameState *state) {
    return cell_to_sector((*state & 0b01111000) >> 3);
}
