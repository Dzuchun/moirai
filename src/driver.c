#include "board.h"
#include "convert.h"
#include "game.h"
#include "player.h"
#include "wins.h"
#include <driver.h>
#include <stdint.h>
#include <stdio.h>

WinSide drive_new(PlayerBrain *player_cross, PlayerBrain *player_circle,
                  FILE *complain_file) {
    Board b;
    BoardPtr board = (int8_t *)&b;
    initial_board(board);
    return drive_to_end(board, player_cross, player_circle, complain_file);
}

WinSide drive_to_end(BoardPtr board, PlayerBrain *player_cross,
                     PlayerBrain *player_circle, FILE *complain_file) {
    WinSide global_winner = Noone;
    WinSide local_winner;
    MoveSide move_side;
    PlayerBrain *active_player;
    int cell;
    SectorInd sector;
    SectorPtr sector_ptr, total_sector;
    GameState *state;
    state = get_game_state(board);
    total_sector = get_sector_board(board, SectorT);
    while (global_winner == Noone) {
        // get move side
        move_side = get_move_side(state);
        switch (move_side) {
        case PlayerCross:
            active_player = player_cross;
            break;
        case PlayerCircle:
            active_player = player_circle;
            break;
        }
        // ask them to move
        int attempts;
        for (attempts = 3; attempts; --attempts) {
            sector = next_move_sector(state);
            if (sector != InvalidSector) {
                // sector is pre-determined
                if (!player_get_fixed_sector(active_player, board, sector,
                                             &cell)) {
                    global_winner = opposite_side(move_side);
                    goto end;
                }
            } else {
                // can move to any sector
                if (!player_get_any_sector(active_player, board, &sector,
                                           &cell)) {
                    global_winner = opposite_side(move_side);
                    goto end;
                }
            }

            if (!is_legal(board, sector, cell, complain_file)) {
                break;
            }
        }
        if (!attempts) {
            global_winner = opposite_side(move_side);
            goto end;
        }

        // set board's cell
        set_cell_board(board, sector, cell, side_to_cell(move_side));
        // change next player to move
        flip_move_side(state);
        // get sector where we'd set the cell in
        sector_ptr = get_sector_board(board, sector);
        // check if someone had won
        local_winner = get_sector_winner(sector_ptr);
        if (local_winner != Noone) {
            // someone had won or it's a draw
            // regardless, set total field accordingly
            set_cell_board(board, SectorT, sector_to_cell(sector),
                           winner_to_cell(local_winner));
        }
        // update global winner
        global_winner = get_sector_winner(total_sector);
    }
end:
    return global_winner;
}

static void game_noop(int i, WinSide side) {}

EvaluationResult evaluate(PlayerBrain *player_cross, PlayerBrain *player_circle,
                          int total_games, GameResultCallback callback) {
    EvaluationResult res;
    WinSide winner;
    res.total_games = total_games;
    res.cross_games = 0;
    res.circle_games = 0;
    res.draw_games = 0;
    if (callback == NULL)
        callback = game_noop;

    for (int i = 0; i < total_games; ++i) {
        // play a game
        winner = drive_new(player_cross, player_circle, NULL);
        // increment a counter
        switch (winner) {
        case CrossPlayer:
            ++res.cross_games;
            break;
        case CirclePlayer:
            ++res.circle_games;
            break;
        case Draw:
            ++res.draw_games;
            break;
        case Noone:
            break;
        }
        // callback
        callback(i, winner);
    }
    return res;
}

static void eval_noop(int i, EvaluationResult evaluation) {}

void evaluate_multiple(PlayerBrain *player_cross, int opponents_count,
                       int exclude_ind, PlayerBrain *players_circle,
                       EvaluationResult *output, int each_games,
                       GameResultCallback game_callback,
                       EvaluationResultCallback callback) {
    EvaluationResult result;
    if (callback == NULL)
        callback = eval_noop;
    for (int i = 0; i < opponents_count; ++i) {
        if (i == exclude_ind) {
            // make it 50%/45%/5%
            result.total_games = each_games;
            // that's 50%
            result.cross_games = each_games / 2;
            // that's 5%
            result.draw_games = result.cross_games / 10;
            // that's the rest (about 45%)
            result.circle_games =
                each_games - result.cross_games - result.draw_games;
        } else {
            result = evaluate(player_cross, players_circle + i, each_games,
                              game_callback);
        }
        output[i] = result;
        callback(i, result);
    }
}
