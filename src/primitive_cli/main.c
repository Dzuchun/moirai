#include <board.h>
#include <cell.h>
#include <convert.h>
#include <game.h>
#include <io.h>
#include <sector.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wins.h>

static void display_state(BoardPtr board);

static void get_move(BoardPtr board, SectorInd *sector, int *cell,
                     int sector_defined);

static void greet_winner(WinSide winner);

int main() {
    Board b;
    BoardPtr bp = (int8_t *)&b;
    WinSide global_winner = Noone, local_winner;
    MoveSide move_side;
    int cell;
    SectorInd sector;
    SectorPtr sector_ptr, total_sector_ptr;
    GameState *state;
    init_wins();

    initial_board(bp);
    state = get_game_state(bp); // it's not changing, actually
    total_sector_ptr =
        get_sector_board(bp, SectorT); // yep. it's not changing too
    while (global_winner == Noone) {
        // show board's current state
        display_state(bp);
        // get move side
        move_side = get_move_side(state);
        // ask them to move
        get_move(bp, &sector, &cell,
                 (sector = next_move_sector(state)) == InvalidSector);
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

    greet_winner(global_winner);
}

static char buf[BUFSIZ];
static void display_state(BoardPtr board) {
    char *bp = buf;
    display_board(&bp, board);
    puts(buf);
}

static int enforce_legal(BoardPtr board, SectorInd *sector, int *cell) {
    CellValue cell_value;
    int verdict = 0;
    // there are exactly 9 cells
    if (*cell < 1 || *cell > 9) {
        fprintf(stderr, "Error: cell %d is not a valid cell\n", *cell);
        verdict |= 0b0001;
    }
    if (*sector == SectorT) {
        fprintf(stderr, "Error: sector T cannot be influenced directly\n");
        verdict |= 0b0010;
    }
    if (*sector == InvalidSector) {
        fprintf(stderr, "Error: invalid sector\n");
        verdict |= 0b0100;
    }
    // can't make a move there, if this cell was already occupied
    cell_value = get_cell_board(board, *sector, *cell);
    if (!verdict && cell_value != Empty) {
        fprintf(stderr, "Error: cell (%d-%d) is already occupied\n", *sector,
                *cell);
        verdict |= 0b1000;
    }
    return verdict;
}

static int parse_cell_ind(char **src, int *cell) {
    char this_char = **src;
    if (this_char < '1' || this_char > '9')
        return -1;
    *src += 1;
    *cell = this_char - '0';
    return 0;
}

static void get_move(BoardPtr board, SectorInd *sector, int *cell,
                     int sector_defined) {
    char *bp;
    char input_sector;
    do {
        bp = buf;
        dstcat(bp, "Please, input your move: ");
        if (sector_defined) {
            display_sector_ind(&bp, *sector);
        }
        puts(buf);
        fgets(buf, BUFSIZ, stdin);
        if (feof(stdin)) {
            display_state(board);
            printf("Goodbye\n");
            exit(0); // ok to do, since that's a simple cli for testing
        }
        bp = buf;
        if (!sector_defined) {
            *sector = InvalidSector;
            parse_sector_ind(&bp, sector);
        }
        *cell = -1;
        parse_cell_ind(&bp, cell);
    } while (enforce_legal(board, sector, cell) > 0);
}

void greet_winner(WinSide side) {
    char *bp = buf;
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
