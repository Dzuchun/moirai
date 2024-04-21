#include <nn/network.h>
#include <player.h>
#include <stdio.h>

FixedSectorBrain bot_neural_fixed_sector();

AnySectorBrain bot_neural_any_sector();

PlayerBrain bot_neural_zeroes(int layers, NNActivationFunction activation);

PlayerBrain bot_neural_random(int layers, float min, float max,
                              NNActivationFunction activation);

PlayerBrain bot_neural_fread(FILE *fin, NNActivationFunction activation);

PlayerBrain bot_neural_diff(PlayerBrain *parent, float max_diff, float min,
                            float max);
