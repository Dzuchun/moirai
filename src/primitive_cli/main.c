#include "player.h"
#include <board.h>
#include <cell.h>
#include <convert.h>
#include <debug.h>
#include <game.h>
#include <io.h>
#include <player/primitive_io.h>
#include <sector.h>
#include <stdint.h>
#include <stdio.h>
#include <wins.h>

extern FILE *playerin, *playerout;

static void greet_winner(BoardPtr board, WinSide winner);

int main() {
    Board b;
    BoardPtr bp = (int8_t *)&b;
    WinSide global_winner = Noone, local_winner;
    MoveSide move_side;
    int cell;
    SectorInd sector;
    SectorPtr sector_ptr, total_sector_ptr;
    GameState *state;
    playerin = stdin;
    playerout = stdout;
    FixedSectorBrain fixed_brain = primitive_io_fixed_sector();
    AnySectorBrain any_brain = primitive_io_any_sector();
    init_wins();
    // print_debug_wins();

    initial_board(bp);
    state = get_game_state(bp); // it's not changing, actually
    total_sector_ptr =
        get_sector_board(bp, SectorT); // yep. it's not changing too
    while (global_winner == Noone) {
        // get move side
        move_side = get_move_side(state);
        // ask them to move
        int attempts;
        for (attempts = 3; attempts; --attempts) {
            sector = next_move_sector(state);
            if (sector != InvalidSector) {
                // sector is pre-determined
                if (!fixed_brain(bp, sector, &cell)) {
                    global_winner = opposite_side(move_side);
                    goto end;
                }
            } else {
                // can move to any sector
                if (!any_brain(bp, &sector, &cell)) {
                    global_winner = opposite_side(move_side);
                    goto end;
                }
            }

            if (!is_legal(bp, sector, cell, stderr)) {
                break;
            }
        }
        if (!attempts) {
            global_winner = opposite_side(move_side);
            goto end;
        }

        // set board's cell
        set_cell_board(bp, sector, cell, side_to_cell(move_side));
        // change next player to move
        flip_move_side(state);
        // get sector where we'd set the cell in
        sector_ptr = get_sector_board(bp, sector);
        // check if someone had won
        local_winner = get_sector_winner(sector_ptr);
        if (local_winner != Noone) {
            // someone had won or it's a draw
            // regardless, set total field accordingly
            set_cell_board(bp, SectorT, sector_to_cell(sector),
                           winner_to_cell(local_winner));
        }
        // update global winner
        global_winner = get_sector_winner(total_sector_ptr);
    }
end:
    greet_winner(bp, global_winner);
}

static char buf[BUFSIZ];

void greet_winner(BoardPtr board, WinSide side) {
    char *bp = buf;
    display_board(&bp, board);
    switch (side) {
    case Cross:
    case Circle:
        dstcat(bp, "\nThe winner is... ");
        display_win_side(&bp, side);
        dstcat(bp, "!\nGrats!\n");
        break;
    case Draw:
        dstcat(bp, "\nIt's a DRAW! What a match!\n");
        break;
    case Noone:
        fprintf(stderr, "\tThats a serious error. Investigate.\n");
    }
    puts(buf);
}
