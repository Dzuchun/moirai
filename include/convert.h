#ifndef CONVERT_H
#define CONVERT_H

#include <cell.h>
#include <game.h>
#include <sector.h>
#include <wins.h>

// Converts move side to cell value corresponding to it
CellValue side_to_cell(MoveSide side);

CellValue winner_to_cell(WinSide side);

int cell_value_to_int(CellValue value);

int sector_to_cell(SectorInd sector);

SectorInd cell_to_sector(int cell);

#endif
