#include "board.h"
#include "sector.h"
#include <player.h>
#include <player/random.h>

static int fixed_sector(BoardPtr board, SectorInd sector, int *cell) {}

FixedSectorBrain bot_random_fixed_sector() { return *fixed_sector; }

static int any_sector(BoardPtr board, SectorInd *sector, int *cell) {}

AnySectorBrain random_any_sector() { return *any_sector; }
