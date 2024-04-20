#include "board.h"
#include "cell.h"
#include "sector.h"
#include <game.h>
#include <io.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <wins.h>

inline void display_win_side(char **dst, WinSide side) {
    switch (side) {
    case Noone:
        dstcat(*dst, "Noone");
        return;
    case CrossPlayer:
        dstcat(*dst, "CROSS player");
        return;
    case CirclePlayer:
        dstcat(*dst, "CIRCLE player");
        return;
    case Draw:
        dstcat(*dst, "DRAW");
        return;
    }
}

inline void display_move_side(char **dst, MoveSide side) {
    switch (side) {
    case PlayerCross:
        dstcat(*dst, "CROSS");
        return;
    case PlayerCircle:
        dstcat(*dst, "CIRCLE");
        return;
    }
}

inline void display_game_state(char **dst, GameState *state) {
    dstcat(*dst, "Next player to move: ");
    display_move_side(dst, get_move_side(state));
    dstcat(*dst, "\nNext move into: ");
    display_sector_ind(dst, next_move_sector(state));
    dstcat(*dst, "\n");
}

inline void display_cell_value(char **dst, CellValue value) {
    char *c = NULL;
    switch (value) {
    case Empty:
        c = (char *)" ";
        break;
    case Cross:
        c = (char *)"X";
        break;
    case Circle:
        c = (char *)"O";
        break;
    case Invalid:
        c = (char *)"@";
        break;
    }
    dstcat(*dst, c);
}

#define __vert "║"
#define __hor "═"
#define __cross "╬"
#define _write_cell(dst, brd, sector, cell)                                    \
    display_cell_value(dst, get_cell_board(brd, Sector##sector, cell));

#define _write_row(dst, brd, s1, s2, s3, c1, c2, c3)                           \
    _write_cell(dst, brd, s1, c1);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s1, c2);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s1, c3);                                             \
    dstcat(*dst, __vert);                                                      \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s2, c1);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s2, c2);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s2, c3);                                             \
    dstcat(*dst, __vert);                                                      \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s3, c1);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s3, c2);                                             \
    dstcat(*dst, __vert);                                                      \
    _write_cell(dst, brd, s3, c3);

#define __divider                                                              \
    "\n" __hor __cross __hor __cross __hor __cross __cross __hor __cross __hor \
        __cross __hor __cross __cross __hor __cross __hor __cross __hor "\n"

inline void display_game_grid(char **dst, BoardPtr board) {
    // Display the mainboard
    _write_row(dst, board, A, B, C, 1, 2, 3);
    dstcat(*dst, __divider);
    _write_row(dst, board, A, B, C, 4, 5, 6);
    dstcat(*dst, __divider);
    _write_row(dst, board, A, B, C, 7, 8, 9);
    dstcat(*dst, __divider);
    dstcat(*dst, __divider);
    _write_row(dst, board, D, E, F, 1, 2, 3);
    dstcat(*dst, __divider);
    _write_row(dst, board, D, E, F, 4, 5, 6);
    dstcat(*dst, __divider);
    _write_row(dst, board, D, E, F, 7, 8, 9);
    dstcat(*dst, __divider);
    dstcat(*dst, __divider);
    _write_row(dst, board, G, H, I, 1, 2, 3);
    dstcat(*dst, __divider);
    _write_row(dst, board, G, H, I, 4, 5, 6);
    dstcat(*dst, __divider);
    _write_row(dst, board, G, H, I, 7, 8, 9);
    dstcat(*dst, "\n==========\n");
    // Display the total board sector
    _write_cell(dst, board, T, 1);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 2);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 3);
    dstcat(*dst, "\n" __hor __cross __hor __cross __hor "\n");
    _write_cell(dst, board, T, 4);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 5);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 6);
    dstcat(*dst, "\n" __hor __cross __hor __cross __hor "\n");
    _write_cell(dst, board, T, 7);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 8);
    dstcat(*dst, __vert);
    _write_cell(dst, board, T, 9);
    dstcat(*dst, "\n");
}

#undef _write_row
#undef _write_cell
#undef __divider
#undef __cross
#undef __vert
#undef __hor

inline void display_board(char **dst, BoardPtr board) {
    display_game_grid(dst, board);
    dstcat(*dst, "------\n");
    display_game_state(dst, get_game_state(board));
}

#define __match_tmp1(l1, l2)                                                   \
    {                                                                          \
    case Sector##l1:                                                           \
        dstcat(*dst, l2);                                                      \
        return;                                                                \
    }

inline void display_sector_ind(char **dst, SectorInd sector) {
    switch (sector) {
    case SectorA:
        dstcat(*dst, "A");
        return;
    case SectorB:
        dstcat(*dst, "B");
        return;
    case SectorC:
        dstcat(*dst, "C");
        return;
    case SectorD:
        dstcat(*dst, "D");
        return;
    case SectorE:
        dstcat(*dst, "E");
        return;
    case SectorF:
        dstcat(*dst, "F");
        return;
    case SectorG:
        dstcat(*dst, "G");
        return;
    case SectorH:
        dstcat(*dst, "H");
        return;
    case SectorI:
        dstcat(*dst, "I");
        return;
    case SectorT:
        dstcat(*dst, "T");
        return;
    default:
        dstcat(*dst, "Any");
        return;
    }
}

#undef __match_tmp1

#define __match_tmp2(l1, l2)                                                   \
    {                                                                          \
    case l2:                                                                   \
        *sector = Sector##l1;                                                  \
        *src += 1;                                                             \
        return 0;                                                              \
    }

inline int parse_sector_ind(char **src, SectorInd *sector) {
    char c = **src;
    switch (c) {
        __match_tmp2(A, 'A') __match_tmp2(B, 'B') __match_tmp2(C, 'C')
            __match_tmp2(D, 'D') __match_tmp2(E, 'E') __match_tmp2(F, 'F')
                __match_tmp2(G, 'G') __match_tmp2(H, 'H') __match_tmp2(I, 'I')
                    __match_tmp2(T, 'T') __match_tmp2(A, 'a')
                        __match_tmp2(B, 'b') __match_tmp2(C, 'c')
                            __match_tmp2(D, 'd') __match_tmp2(E, 'e')
                                __match_tmp2(F, 'f') __match_tmp2(G, 'g')
                                    __match_tmp2(H, 'h') __match_tmp2(I, 'i')
                                        __match_tmp2(T, 't') default
            : return -1;
    }
}

#undef __match_tmp2
