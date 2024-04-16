#include <board.h>
#include <util.h>

#include <stdlib.h>

#define PRINT_CELL(out, board, cell)                                           \
    {                                                                          \
        CellValue cv = get_cell_value(board, cell);                            \
        *out++ = CELL_REPR(cv);                                                \
    };

#define PRINT_LINE(out, board, cell1, cell2, cell3, cell4, cell5, cell6,       \
                   cell7, cell8, cell9)                                        \
    {                                                                          \
        PRINT_CELL(out, board, cell1);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell2);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell3);                                         \
        *out++ = BORDER_VERT;                                                  \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell4);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell5);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell6);                                         \
        *out++ = BORDER_VERT;                                                  \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell7);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell8);                                         \
        *out++ = BORDER_VERT;                                                  \
        PRINT_CELL(out, board, cell9);                                         \
        *out++ = '\n';                                                         \
    };

#define PRINT_SEPR(out)                                                        \
    {                                                                          \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_CROSS;                                                 \
        *out++ = BORDER_CROSS;                                                 \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_CROSS;                                                 \
        *out++ = BORDER_CROSS;                                                 \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = BORDER_HOR;                                                   \
        *out++ = '\n';                                                         \
    };

#define PRINT_STR(out, str_arr)                                                \
    {                                                                          \
        char *str = (char *)str_arr;                                           \
        for (char c; (c = *str++) != '\0'; *out++ = c)                         \
            ;                                                                  \
    }

int print_board(Board b, char *buf) {
    char *start = buf;
    CellValue cv;
    PRINT_STR(buf, "\nMain board:\n");
    PRINT_LINE(buf, b, A_1, A_2, A_3, B_1, B_2, B_3, C_1, C_2, C_3);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, A_4, A_5, A_6, B_4, B_5, B_6, C_4, C_5, C_6);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, A_7, A_8, A_9, B_7, B_8, B_9, C_7, C_8, C_9);
    PRINT_SEPR(buf);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, D_1, D_2, D_3, E_1, E_2, E_3, F_1, F_2, F_3);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, D_4, D_5, D_6, E_4, E_5, E_6, F_4, F_5, F_6);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, D_7, D_8, D_9, E_7, E_8, E_9, F_7, F_8, F_9);
    PRINT_SEPR(buf);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, G_1, G_2, G_3, H_1, H_2, H_3, I_1, I_2, I_3);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, G_4, G_5, G_6, H_4, H_5, H_6, I_4, I_5, I_6);
    PRINT_SEPR(buf);
    PRINT_LINE(buf, b, G_7, G_8, G_9, H_7, H_8, H_9, I_7, I_8, I_9);

    PRINT_STR(buf, "\nAuxillary board:\n");
    PRINT_CELL(buf, b, T_1);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_2);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_3);
    PRINT_STR(buf, "\n-+-+-\n");
    PRINT_CELL(buf, b, T_4);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_5);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_6);
    PRINT_STR(buf, "\n-+-+-\n");
    PRINT_CELL(buf, b, T_7);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_8);
    *buf++ = '|';
    PRINT_CELL(buf, b, T_9);
    *buf++ = '\n';

    *buf++ = '\0';
    return buf - start;
}

#define __CELL_SECTOR_MATCH(sector, digi)                                      \
    switch (digi) {                                                            \
    case 1:                                                                    \
        return sector##_1;                                                     \
    case 2:                                                                    \
        return sector##_2;                                                     \
    case 3:                                                                    \
        return sector##_3;                                                     \
    case 4:                                                                    \
        return sector##_4;                                                     \
    case 5:                                                                    \
        return sector##_5;                                                     \
    case 6:                                                                    \
        return sector##_6;                                                     \
    case 7:                                                                    \
        return sector##_7;                                                     \
    case 8:                                                                    \
        return sector##_8;                                                     \
    case 9:                                                                    \
        return sector##_9;                                                     \
    default:                                                                   \
        return NullCell;                                                       \
    }

Cell parse_cell(char *s) {
    char sect = *s++, digi = *s - '0';
    switch (sect) {
    case 'A':
        __CELL_SECTOR_MATCH(A, digi);
    case 'B':
        __CELL_SECTOR_MATCH(B, digi);
    case 'C':
        __CELL_SECTOR_MATCH(C, digi);
    case 'D':
        __CELL_SECTOR_MATCH(D, digi);
    case 'E':
        __CELL_SECTOR_MATCH(E, digi);
    case 'F':
        __CELL_SECTOR_MATCH(F, digi);
    case 'G':
        __CELL_SECTOR_MATCH(G, digi);
    case 'H':
        __CELL_SECTOR_MATCH(H, digi);
    case 'I':
        __CELL_SECTOR_MATCH(I, digi);
    case 'T':
        __CELL_SECTOR_MATCH(T, digi);
    default:
        return NullCell;
    }
}

#define _FOLD(board, op)                                                       \
    (board)[0] op(board)[1] op(board)[2] op(board)[3] op(board)[4] op(board)   \
        [5] op(board)[6] op(board)[7] op(board)[8] op(board)[9] op(            \
            board)[10] op(board)[11] op(board)[12] op(board)[13] op(board)     \
            [14] op(board)[15] op(board)[16] op(board)[17] op(board)[18] op(   \
                board)[19] op(board)[20] op(board)[21] op(board)[22]

#define _INIT_BOARDS_SIDE(dst, side)                                           \
    {                                                                          \
        Board b;                                                               \
        for (int i = 0; i < CELL_COUNT; ++i) {                                 \
            dst[i] = new_board();                                              \
            dst[i][i >> 2] = (side << ((i & 0b11) << 1));                      \
        }                                                                      \
    }

Board tmp_b;
CellValue get_cell_value(Board b, Cell cell) {
    int cell_no = (int)cell;
    // zero-out tempboard
    ZERO(tmp_b);
    // copy current board there
    PRODUCT(tmp_b, tmp_b, b, |);
    // zero-out everything else
    PRODUCT(tmp_b, tmp_b, cell_mask_tot[cell_no], &);
    // try compating it with various boards
    if (EQUALS(tmp_b, cell_mask_empty[cell_no]))
        return Empty;
    if (EQUALS(tmp_b, cell_mask_tic[cell_no]))
        return Tic;
    if (EQUALS(tmp_b, cell_mask_tac[cell_no]))
        return Tac;
    return NullValue;
}

CellValue set_cell_value(Board b, Cell cell, CellValue value) {
    // set tmp_b to desired variant
    int cell_no = (int)cell;
    switch (value) {
    case Tic:
        tmp_b = cell_mask_tic[cell_no];
        break;
    case Tac:
        tmp_b = cell_mask_tac[cell_no];
        break;
    case Empty:
        ZERO(tmp_b);
        break;
    case NullValue:
        return NullValue;
    }
    // at this point, tmp_b has correct bits at correct position
    // now, we just need to set b to these bits
    // to do that, we first clear required bits
    Board mask = cell_mask_tot[cell_no];
    UNARY(mask, mask, ~);    // revert the mask
    PRODUCT(b, b, mask, &);  // AND with board, to ensure these bits are 0
    PRODUCT(b, b, tmp_b, |); // OR with created board
    UNARY(mask, mask, ~);    // revert mask back!
    return NullValue;
}

Board new_board() { return calloc(BOARD_DATA_SIZE, sizeof(unsigned char)); }

void free_board(Board board) { free(board); }

Board cell_mask_tic[CELL_COUNT];
Board cell_mask_tac[CELL_COUNT];
Board cell_mask_tot[CELL_COUNT];
Board cell_mask_empty[CELL_COUNT];

void init_boards() {
    _INIT_BOARDS_SIDE(cell_mask_tic, Tic);
    _INIT_BOARDS_SIDE(cell_mask_tac, Tac);
    _INIT_BOARDS_SIDE(cell_mask_empty, Empty);
    _INIT_BOARDS_SIDE(cell_mask_tot, 0b11);
    tmp_b = new_board();
}

Cell from_sector_num(BoardSector sector, char digi) {
    if (digi < '1' || digi > '9')
        return NullCell;
    int num = digi - '0';
    return (Cell)(((int)sector) * 9 + num);
}
