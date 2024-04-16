// Defines primitives for win checks

#ifndef TOES_H
#define TOES_H 1

#include <board.h>
#include <util.h>

typedef CellValue WinSide;

#define COL_TOES 3
#define ROW_TOES 3
#define DIA_TOES 2
#define TOT_TOES (COL_TOES + ROW_TOES + DIA_TOES)
extern Board tic_toes[SECTORS_NUM][TOT_TOES];
extern Board tac_toes[SECTORS_NUM][TOT_TOES];
extern Board tot_toes[SECTORS_NUM][TOT_TOES];

// Initializes toe static arrays
void init_toes();

// Checks board's sector for any side winning condition
WinSide check_sector(Board b, BoardSector sector);

#endif
