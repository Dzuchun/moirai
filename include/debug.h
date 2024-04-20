#include "sector.h"
#include "wins.h"
#include <stdio.h>
#ifdef DEBUG_BUILD
#ifndef DEBUG_H
#define DEBUG_H

#include "board.h"

// Prints board in a debug-able format
void debug_print_board(BoardPtr board);

// Prints wins in a debug-able format
void print_debug_wins();

// Report value
void debug_report(int val, const char *ctx);

// Prints sector in a debug mode
void print_sector_debug(SectorPtr sector);

#endif
#endif
