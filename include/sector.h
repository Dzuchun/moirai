#ifndef SECTOR_H
#define SECTOR_H

#include <cell.h>
#include <stdint.h>

struct _sector_ptr {
    int8_t *data;
    int8_t offset;
};
// Represents a pointer to exactly 9 cells
//
// 9 cells is a bad number of cells to have, since it's kinda hard to pack them
// together inside two bytes, while 3 bytes would be insanely inefficient. So
// instead, sectors will be just fancy pointers to a region of 9 cells
typedef struct _sector_ptr SectorPtr;

// Sets a certain cell in a sector to some value
void sector_set_cell(SectorPtr sector, int idx, CellValue cell);

// Gets value of a certain cell in the sector
CellValue sector_get_cell(SectorPtr sector, int idx);

// Represents 8 sector of the board, takes 18 bytes total
typedef int8_t *Sector8;

enum _sector_ind {
    SectorA = 1,
    SectorB = 2,
    SectorC = 3,
    SectorD = 4,
    SectorE = 5,
    SectorF = 6,
    SectorG = 7,
    SectorH = 8,
    SectorI = 9,
    SectorT = 0, // total sector, for tracking entire game winner
    InvalidSector = 10,
};
typedef enum _sector_ind SectorInd;

#endif
