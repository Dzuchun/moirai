#include "board.h"
#include "sector.h"
#include <player.h>
#include <stdio.h>

inline void dispose(PlayerBrain *player) {
    if (player->distructor != NULL) {
        player->distructor(player->state);
    }
}

inline int player_get_any_sector(PlayerBrain *player, BoardPtr board,
                                 SectorInd *sector, int *cell) {
    return player->any(board, sector, cell, player->state);
}

inline int player_get_fixed_sector(PlayerBrain *player, BoardPtr board,
                                   SectorInd sector, int *cell) {
    return player->fixed(board, sector, cell, player->state);
}
