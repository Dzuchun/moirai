#include <board.h>
#include <toes.h>
#include <util.h>

#define _WRITE_TOE_INNER(dst, cell1, cell2, cell3, side)                       \
    {                                                                          \
        Board res = new_board();                                               \
        PRODUCT(res, (cell_mask_##side)[cell1], (cell_mask_##side)[cell2], |); \
        PRODUCT(res, res, (cell_mask_##side)[cell3], |);                       \
        dst = res;                                                             \
    }

#define _WRITE_TOES(dst, sector, offset, side)                                 \
    {                                                                          \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_1, sector##_2,        \
                         sector##_3, side);                                    \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_4, sector##_5,        \
                         sector##_6, side);                                    \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_7, sector##_8,        \
                         sector##_9, side);                                    \
                                                                               \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_1, sector##_4,        \
                         sector##_7, side);                                    \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_2, sector##_5,        \
                         sector##_8, side);                                    \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_3, sector##_6,        \
                         sector##_9, side);                                    \
                                                                               \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_1, sector##_5,        \
                         sector##_9, side);                                    \
        _WRITE_TOE_INNER(dst[sector][offset++], sector##_7, sector##_5,        \
                         sector##_3, side);                                    \
    }

#define _WRITE_TOES_ALL(dst, side)                                             \
    {                                                                          \
        int offset = 0;                                                        \
        _WRITE_TOES(dst, A, offset, side);                                     \
        _WRITE_TOES(dst, B, offset, side);                                     \
        _WRITE_TOES(dst, C, offset, side);                                     \
        _WRITE_TOES(dst, D, offset, side);                                     \
        _WRITE_TOES(dst, E, offset, side);                                     \
        _WRITE_TOES(dst, F, offset, side);                                     \
        _WRITE_TOES(dst, G, offset, side);                                     \
        _WRITE_TOES(dst, H, offset, side);                                     \
        _WRITE_TOES(dst, I, offset, side);                                     \
        _WRITE_TOES(dst, T, offset, side);                                     \
    }

Board tic_toes[SECTORS_NUM][TOT_TOES];
Board tac_toes[SECTORS_NUM][TOT_TOES];
Board tot_toes[SECTORS_NUM][TOT_TOES];
static Board tmp_b;

void init_toes() {
    _WRITE_TOES_ALL(tic_toes, tic);
    _WRITE_TOES_ALL(tac_toes, tac);
    _WRITE_TOES_ALL(tot_toes, tot);
    tmp_b = new_board();
}

#define _CHECK_TOE(board, side, toe, ret)                                      \
    {                                                                          \
        ZERO(board);                                                           \
        PRODUCT(tmp_b, tmp_b, board, |);                                       \
        PRODUCT(tmp_b, tmp_b, tot_toes[toe], &);                               \
        if (EQUALS(tmp_b, cell_mask_##side[toe]))                              \
            return ret;                                                        \
    }

WinSide check_sector(Board b, BoardSector sector) {
    for (int toe = 0; toe < TOT_TOES; ++toe) {
        _CHECK_TOE(tmp_b, tic, toe, Tic);
    }
    return Empty;
}
