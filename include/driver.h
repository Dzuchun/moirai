

// This defines a so-called "game driver"
//
// It must play a game and return it's result automatically

#include "board.h"
#include "player.h"
#include "wins.h"
#include <stdio.h>

WinSide drive_new(PlayerBrain player_cross, PlayerBrain player_circle,
                  FILE *complain_file);

WinSide drive_to_end(BoardPtr board, PlayerBrain player_cross,
                     PlayerBrain player_circle, FILE *complain_file);

struct _evaluation_result {
    int total_games;
    int cross_games;
    int circle_games;
    int draw_games;
};
// Defines result of multiple games played between two players
typedef struct _evaluation_result EvaluationResult;

typedef void (*GameResultCallback)(int, WinSide);

EvaluationResult evaluate(PlayerBrain player_cross, PlayerBrain player_circle,
                          int total_games, GameResultCallback callback);

typedef void (*EvaluationResultCallback)(int, EvaluationResult);

// Note: you can ask this function to play a player with itself. However, in
// this case player's brain might misbehave. To avoid that, please specify
// [exclude_ind] to be an index of the cross_player in array.
//
// In this case, result of their game would be a generic determined 50%/45%/5%
//
// If you don't want to exclude anyone, just pass -1, or any other index that
// would never be reached
void evaluate_multiple(PlayerBrain player_cross, int opponents_count,
                       int exclude_ind, PlayerBrain *players_circle,
                       EvaluationResult *output, int each_games,
                       GameResultCallback game_callback,
                       EvaluationResultCallback callback);
