

// This defines a so-called "game driver"
//
// It must play a game and return it's result automatically

#include "board.h"
#include "game.h"
#include "player.h"
#include "wins.h"
#include <stdio.h>

WinSide drive_new(PlayerBrain player_cross, PlayerBrain player_circle,
                  FILE *complain_file);

WinSide drive_to_end(BoardPtr board, PlayerBrain player_cross,
                     PlayerBrain player_circle, FILE *complain_file);
