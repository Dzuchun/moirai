#ifndef UTIL_H
#define UTIL_H 1

#include <board.h>

#define _UNARY_BYTE(dest, board, op, idx) (dest)[idx] = op((board)[idx]);
#define UNARY(dest, board, op)                                                 \
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

#define PRODUCT(dest, board1, board2, op)                                      \
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

#define EQUALS(b1, b2)                                                         \
    (((b1)[0] == (b2)[0]) && ((b1)[1] == (b2)[1]) && ((b1)[2] == (b2)[2]) &&   \
     ((b1)[3] == (b2)[3]) && ((b1)[4] == (b2)[4]) && ((b1)[5] == (b2)[5]) &&   \
     ((b1)[6] == (b2)[6]) && ((b1)[7] == (b2)[7]) && ((b1)[8] == (b2)[8]) &&   \
     ((b1)[9] == (b2)[9]) && ((b1)[10] == (b2)[10]) &&                         \
     ((b1)[10] == (b2)[10]) && ((b1)[11] == (b2)[11]) &&                       \
     ((b1)[12] == (b2)[12]) && ((b1)[13] == (b2)[13]) &&                       \
     ((b1)[14] == (b2)[14]) && ((b1)[15] == (b2)[15]) &&                       \
     ((b1)[16] == (b2)[16]) && ((b1)[17] == (b2)[17]) &&                       \
     ((b1)[18] == (b2)[18]) && ((b1)[19] == (b2)[19]) &&                       \
     ((b1)[20] == (b2)[20]) && ((b1)[21] == (b2)[21]) &&                       \
     ((b1)[22] == (b2)[22]))

#define ZERO(b)                                                                \
    (b)[0] = (b)[1] = (b)[2] = (b)[3] = (b)[4] = (b)[5] = (b)[6] = (b)[7] =    \
        (b)[8] = (b)[9] = (b)[10] = (b)[11] = (b)[12] = (b)[13] = (b)[14] =    \
            (b)[15] = (b)[16] = (b)[17] = (b)[18] = (b)[19] = (b)[20] =        \
                (b)[21] = (b)[22] = 0

#endif
