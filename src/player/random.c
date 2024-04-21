#include <board.h>
#include <cell.h>
#include <player.h>
#include <player/random.h>
#include <sector.h>
#include <stdlib.h>
#include <wins.h>

static void generate_valid_cell(BoardPtr board, SectorInd sector, int *cell) {
    if (get_sector_winner(get_sector_board(board, sector)) != Noone)
        // well, this is rigged -- we can't make a move there
        return;
    // we'll make 20 attempts
    for (int i = 20; i; --i) {
        int cell_ind = random() % 9 + 1; // cells are 1-9
        if (get_cell_board(board, sector, cell_ind) == Empty) {
            *cell = cell_ind;
            break;
        }
    }
}

static void generate_valid_sector(BoardPtr board, SectorInd *sector) {
    // we'll make 20 attempts
    for (int i = 20; i; --i) {
        SectorInd sector_ind = random() % 9 + 1; // cells are 1-9
        if (get_sector_winner(get_sector_board(board, sector_ind)) == Noone) {
            *sector = sector_ind;
            break;
        }
    }
}

static int fixed_sector(BoardPtr board, SectorInd sector, int *cell,
                        void *state) {
    generate_valid_cell(board, sector, cell);
    return 1;
}

FixedSectorBrain bot_random_fixed_sector() { return &fixed_sector; }

static int any_sector(BoardPtr board, SectorInd *sector, int *cell,
                      void *state) {
    generate_valid_sector(board, sector);
    generate_valid_cell(board, *sector, cell);
    return 1;
}

AnySectorBrain bot_random_any_sector() { return &any_sector; }

PlayerBrain bot_random_brain() {
    PlayerBrain brain;
    brain.fixed = bot_random_fixed_sector();
    brain.any = bot_random_any_sector();
    brain.state = NULL;
    brain.distructor = NULL;
    return brain;
}
