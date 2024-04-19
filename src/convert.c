#include <cell.h>
#include <convert.h>
#include <game.h>
#include <sector.h>
#include <wins.h>

inline CellValue side_to_cell(MoveSide side) {
    switch (side) {
    case PlayerCross:
        return Cross;
    case PlayerCircle:
        return Circle;
    }
}

inline CellValue winner_to_cell(WinSide winner) {
    switch (winner) {
    case Noone:
        return Empty;
    case CrossPlayer:
        return Cross;
    case CirclePlayer:
        return Circle;
    case Draw:
        return Invalid;
    }
}

inline int cell_value_to_int(CellValue value) { return (int)value; }

inline int sector_to_cell(SectorInd sector) {
    switch (sector) {
    case SectorA:
        return 1;
    case SectorB:
        return 2;
    case SectorC:
        return 3;
    case SectorD:
        return 4;
    case SectorE:
        return 5;
    case SectorF:
        return 6;
    case SectorG:
        return 7;
    case SectorH:
        return 8;
    case SectorI:
        return 9;
    case SectorT:
    case InvalidSector:
        return -1;
    }
}

inline SectorInd cell_to_sector(int cell) {
    switch (cell) {
    case 1:
        return SectorA;
    case 2:
        return SectorB;
    case 3:
        return SectorC;
    case 4:
        return SectorD;
    case 5:
        return SectorE;
    case 6:
        return SectorF;
    case 7:
        return SectorG;
    case 8:
        return SectorH;
    case 9:
        return SectorI;
    default:
        return InvalidSector;
    }
}
