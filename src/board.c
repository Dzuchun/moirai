#include <board.h>
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

#define _SECTOR_SIZE 3
#define _SECTOR_AREA _SECTOR_SIZE *_SECTOR_SIZE
#define _BOARD_SIZE _SECTOR_AREA *_SECTOR_AREA
#define _CELL_COUNT _BOARD_SIZE + _SECTOR_AREA + 1

#define _FOLD(board, op)                                                       \
    (board)[0] op(board)[1] op(board)[2] op(board)[3] op(board)[4] op(board)   \
        [5] op(board)[6] op(board)[7] op(board)[8] op(board)[9] op(            \
            board)[10] op(board)[11] op(board)[12] op(board)[13] op(board)     \
            [14] op(board)[15] op(board)[16] op(board)[17] op(board)[18] op(   \
                board)[19] op(board)[20] op(board)[21] op(board)[22]

#define _UNARY_BYTE(dest, board, op, idx) (dest)[idx] = op((board)[idx]);
#define _UNARY(dest, board, op)                                                \
    _UNARY_BYTE(dest, board, op, 0);                                           \
    _UNARY_BYTE(dest, board, op, 1);                                           \
    _UNARY_BYTE(dest, board, op, 2);                                           \
    _UNARY_BYTE(dest, board, op, 3);                                           \
    _UNARY_BYTE(dest, board, op, 4);                                           \
    _UNARY_BYTE(dest, board, op, 5);                                           \
    _UNARY_BYTE(dest, board, op, 6);                                           \
    _UNARY_BYTE(dest, board, op, 7);                                           \
    _UNARY_BYTE(dest, board, op, 8);                                           \
    _UNARY_BYTE(dest, board, op, 9);                                           \
    _UNARY_BYTE(dest, board, op, 10);                                          \
    _UNARY_BYTE(dest, board, op, 11);                                          \
    _UNARY_BYTE(dest, board, op, 12);                                          \
    _UNARY_BYTE(dest, board, op, 13);                                          \
    _UNARY_BYTE(dest, board, op, 14);                                          \
    _UNARY_BYTE(dest, board, op, 15);                                          \
    _UNARY_BYTE(dest, board, op, 16);                                          \
    _UNARY_BYTE(dest, board, op, 17);                                          \
    _UNARY_BYTE(dest, board, op, 18);                                          \
    _UNARY_BYTE(dest, board, op, 19);                                          \
    _UNARY_BYTE(dest, board, op, 20);                                          \
    _UNARY_BYTE(dest, board, op, 21);                                          \
    _UNARY_BYTE(dest, board, op, 22);

#define _PRODUCT_BYTE(dest, board1, board2, op, idx)                           \
    (dest)[idx] = (board1)[idx] op(board2)[idx];

#define _PRODUCT(dest, board1, board2, op)                                     \
                                                                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 0);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 1);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 2);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 3);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 4);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 5);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 6);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 7);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 8);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 9);                                \
    _PRODUCT_BYTE(dest, board1, board2, op, 10);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 11);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 12);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 13);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 14);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 15);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 16);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 17);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 18);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 19);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 20);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 21);                               \
    _PRODUCT_BYTE(dest, board1, board2, op, 22);

#define _ZERO_BOARD                                                            \
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char _zero_board[] = _ZERO_BOARD;

#define _ONE_BOARD                                                             \
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned char _one_board[] = _ONE_BOARD;

Board _cell_mask[_CELL_COUNT];
void init_boards() {
    Board b;
    int j;
    for (int i = 0; i < _CELL_COUNT; ++i) {
        b = new_board();
        j = i >> 2; // index of a byte to write to
        b[j] = (0b11 << ((i & 0b11) << 1));
        _cell_mask[i] = b;
    }
}

CellValue get_cell_value(Board b, Cell cell) {
    Board *mask = _cell_mask + (int)cell, tmp_b = new_board();
    char tmp_ch;
    _PRODUCT(tmp_b, *mask, b, &);
    tmp_ch = _FOLD(tmp_b, |);
    while (tmp_ch > 0b11)
        tmp_ch >>= 2;
    return (CellValue)tmp_ch;
}

CellValue set_cell_value(Board b, Cell cell, CellValue value) {
    Board *mask = _cell_mask + (int)cell, tmp_b = new_board();
    int cell_value = (int)value;
    _PRODUCT(tmp_b, *mask, tmp_b, &cell_value |);
    cell_value <<= 2;
    _PRODUCT(tmp_b, *mask, tmp_b, &cell_value |);
    cell_value <<= 2;
    _PRODUCT(tmp_b, *mask, tmp_b, &cell_value |);
    cell_value <<= 2;
    _PRODUCT(tmp_b, *mask, tmp_b, &cell_value |);
    // at this point, tmp_b has correct bits at correct position
    // now, we just need to set b to these bits
    // to do that, we first clear required bits
    _UNARY(*mask, *mask, ~);  // revert the mask
    _PRODUCT(b, b, *mask, &); // AND with board, to ensure these bits are 0
    _PRODUCT(b, b, tmp_b, |); // OR with created board
    _UNARY(*mask, *mask, ~);  // revert mask back!
    return NullValue;
}

Board new_board() { return calloc(BOARD_DATA_SIZE, sizeof(unsigned char)); }

void free_board(Board board) { free(board); }
