/*
#define GAME_SIZE 3
#define SECTOR_SIZE (BOARD_SIZE * BOARD_SIZE)
#define BOARD_SIZE (SECTOR_SIZE * SECTOR_SIZE)
*/

#define EMPTY 0b00     // no symbol
#define TIC 0b10       // X symbol
#define TAC 0b01       // O symbol
#define NULL_CELL 0b11 // NULL symbol, represents something went wrong
enum cell_value {
    Empty = EMPTY,
    Tic = TIC,
    Tac = TAC,
    NullValue = NULL_CELL,
};
typedef enum cell_value CellValue;

#define BOARD_DATA_SIZE 23
typedef unsigned char *Board;

#define BORDER_VERT '|'
#define BORDER_HOR '-'
#define BORDER_CROSS '+'
#define CELL_REPR(cell)                                                        \
    (cell == Empty) ? ' ' : (cell == Tic) ? 'X' : (cell == Tac) ? 'O' : '@';

// Must be called before any usage of functions inside.
void init_boards();

// Prints board to buffer
//
// Assumes there's enough space for the whole board
int print_board(Board board, char *buf);

#define CELL_SECTOR(sector, no)                                                \
    sector##_1 = no * 9 + 1, sector##_2 = no * 9 + 2, sector##_3 = no * 9 + 3, \
    sector##_4 = no * 9 + 4, sector##_5 = no * 9 + 5, sector##_6 = no * 9 + 6, \
    sector##_7 = no * 9 + 7, sector##_8 = no * 9 + 8, sector##_9 = no * 9 + 9,

enum cell {
    NullCell = 0, // invalid cell
    CELL_SECTOR(A, 0) CELL_SECTOR(B, 1) CELL_SECTOR(C, 2) CELL_SECTOR(D, 3)
        CELL_SECTOR(E, 4) CELL_SECTOR(F, 5) CELL_SECTOR(G, 6) CELL_SECTOR(H, 7)
            CELL_SECTOR(I, 8) CELL_SECTOR(T, 9)

};

typedef enum cell Cell;

// Parses cell from a supplied string
//
// Expected format is [A-I][1-9]. Rest of the string is ignored
//
// If no valid cell is to be parsed, NullCell is returned
Cell parse_cell(char *s);

// Get's stored cell's value
//
// If provided cell is invalid, returns NullValue to explicitly indicate error
CellValue get_cell_value(Board board, Cell cell);

// Stores provided cell value
//
// On error, returns previous cell value, or a NullValue to indicate invalid
// provided cell or value.
//
// Invalid value will not be stored.
CellValue set_cell_value(Board board, Cell cell, CellValue value);

// Creates new board filled with nothing
Board new_board();

// Frees memory occupied by a board
void free_board(Board board);
