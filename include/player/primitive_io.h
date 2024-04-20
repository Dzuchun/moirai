#ifndef PLAYER_PRIMITIVE_IO
#define PLAYER_PRIMITIVE_IO

#include "player.h"
#include <stdio.h>

// A player that gets board printed for them, and in general is supposed to be a
// human being using a terminal
//
// If you plan on using this player, don't forget to set it's input and output
// files
//
// Once input file end is reached - player is considered surrendered

// TODO: I can actually force brain requester specify there automatically via
// variadic functions.

extern FILE *playerin, *playerout;

FixedSectorBrain primitive_io_fixed_sector();

AnySectorBrain primitive_io_any_sector();

#endif
