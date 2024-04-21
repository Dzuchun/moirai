#include "nn/network.h"
#include <driver.h>
#include <io.h>
#include <math.h>
#include <player.h>
#include <player/neural.h>
#include <player/random.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wins.h>

static PlayerBrain player_cross, player_circle;
static int games_count, games_count_len;

void parse_clargs(int argc, char **argv);

void seed_random();

static char *buf;
void setup_output();
void react_to_win(int, WinSide);

int main(int argc, char **argv) {
    EvaluationResult result;
    parse_clargs(argc, argv);
    setup_output();
    // init wins, as they are used in any case, and it's callers responsibillity
    // to ensure that they are init
    init_wins();
    // create a buffer for our output
    int offset = 25 + 2 * games_count_len;
    buf = calloc(offset, sizeof(char));
    for (int i = 0; i < offset; ++i)
        buf[i] = ' ';
    result = evaluate(&player_cross, &player_circle, games_count, react_to_win);
    printf(
        "\nCross wins: %*d/%*d (%.3f%%)\nCircle wins: %*d/%*d (%.3f%%)\nDraws: "
        "%*d/%*d (%.3f%%)",
        games_count_len, result.cross_games, games_count_len, games_count,
        ((float)result.cross_games) / games_count * 100, games_count_len,
        result.circle_games, games_count_len, games_count,
        ((float)result.circle_games) / games_count * 100, games_count_len,
        result.draw_games, games_count_len, games_count,
        ((float)result.draw_games) / games_count * 100);
    free(buf);
    dispose(&player_cross);
    dispose(&player_circle);
}

void parse_clargs(int argc, char **argv) {
    // MOCK (for now)
    player_cross = bot_neural_random(5, -2.0, 2.0, erff);
    // player_circle = bot_neural_random(5, 0.0, 2.0, erff);
    player_circle = bot_neural_diff(&player_cross, 0.1, -2.0, 2.0);
    // player_circle = bot_neural_diff(&player_cross, 2.0, -2.0, 2.0);
    // player_circle = bot_random_brain();
    seed_random(); // since they will need it
    games_count = 1000;
    games_count_len = 6;
}

void seed_random() {
    int seed;
    FILE *rand = fopen("/dev/random", "r");
    fread_unlocked(&seed, sizeof(seed), 1, rand);
    fclose(rand);
    srand(seed);
}

void setup_output() {
    // make stdout unbuffered
    setbuf(stdout, NULL);
}

#define write_games(out, current, total, total_len)                            \
    {                                                                          \
        sprintf(out, "\rGames: %*d/%*d (%.2f%%)", total_len, current,          \
                total_len, total, ((float)current) / total * 100);             \
    }

void react_to_win(int i, WinSide winner) {
    if (winner == Noone)
        fprintf(stderr, "Game no.%d was won by noone. Probably investigate",
                i + 1);
    // display_cell_value(&buf_end, winner_to_cell(winner));
    write_games(buf, (i + 1), games_count, games_count_len);
    dispose(&player_circle);
    player_circle = bot_neural_diff(&player_cross, 0.1, -2.0, 2.0);
    // draw a buffer to stdout
    fputs(buf, stdout);
}
