#ifndef CELL_H
#define CELL_H

#include <stdint.h>

// Represents value of a single cell
enum _cell_value {
    Empty = 0b00,
    Cross = 0b01,
    Circle = 0b10,
    Invalid = 0b11,
};
// Represents value of a single cell
typedef enum _cell_value CellValue;
typedef enum _cell_value *CellValuePtr;

// Represents eight cell values
typedef int16_t CellValue8;
typedef int16_t *CellValue8Ptr;

// Gets a single cell value from packed value8
CellValue get_value4(CellValue8 value4, int idx);

// Sets a single cell value in packed value8
void set_value4(CellValue8 *value4, int idx, CellValue value);

// Created CellValue8 with all values set to 0
CellValue8 cell_value4_empty();

#endif
