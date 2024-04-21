#include <board.h>
#include <nn/network.h>
#include <player.h>
#include <player/neural.h>
#include <sector.h>
#include <stdio.h>
#include <stdlib.h>
#include <wins.h>

static void bot_neural_free(void *state) {
    NNFree(state);
    free(state);
}

static PlayerBrain bot_neural_with_network(NNInstance instance) {
    PlayerBrain res;
    NNInstance *state;
    res.any = bot_neural_any_sector();
    res.fixed = bot_neural_fixed_sector();
    state = calloc(1, sizeof(NNInstance));
    *state = instance;
    res.state = state;
    res.distructor = *bot_neural_free;
    return res;
}

inline PlayerBrain bot_neural_zeroes(int layers,
                                     NNActivationFunction activation) {
    return bot_neural_with_network(NNZeroes(layers, activation));
}

inline PlayerBrain bot_neural_random(int layers, float min, float max,
                                     NNActivationFunction activation) {
    return bot_neural_with_network(NNRandom(layers, min, max, activation));
}

inline PlayerBrain bot_neural_fread(FILE *fin,
                                    NNActivationFunction activation) {
    return bot_neural_with_network(NNfread(fin, activation));
}

inline PlayerBrain bot_neural_diff(PlayerBrain *parent, float max_diff,
                                   float min, float max) {
    return bot_neural_with_network(
        NNDiff((NNInstance *)parent->state, max_diff, min, max));
}

inline static void embed_board(BoardPtr board, float *dst) {
    int bi, bt;
    for (int i = 0; i < NNLAYER_SIZE; ++i) {
        bi = (i >> 3);
        bt = (i & 0b111);
        dst[i] = ((board[bi] >> bt) & 0b1) * 1.0;
    }
}

struct _bit_weight {
    int bit;
    float weight;
};

static int comp(const void *c1, const void *c2) {
    struct _bit_weight *w1 = (struct _bit_weight *)c1;
    struct _bit_weight *w2 = (struct _bit_weight *)c2;
    if (w1->weight < w2->weight)
        return 1;
    if (w1->weight > w2->weight)
        return -1;
    return 0;
}

#define _to_bit_weights(weights, bit_weights)                                  \
    {                                                                          \
        for (int i = 0; i < NNLAYER_SIZE; ++i) {                               \
            bit_weights[i].weight = weights[i];                                \
            bit_weights[i].bit = i;                                            \
        }                                                                      \
        qsort(bit_weights, NNLAYER_SIZE, sizeof(struct _bit_weight), comp);    \
    }

inline static void apply_weights(BoardPtr board, void *state,
                                 struct _bit_weight *weights) {
    NNInstance *network = state;
    float data[NNLAYER_SIZE];
    // first, convert board to data
    embed_board(board, data);
    // then, apply the network itself
    NNapply(network, data);
    // then, transform them to bit-weights
    // and sort them
    _to_bit_weights(data, weights);
}

static int fixed_sector(BoardPtr board, SectorInd sector, int *cell,
                        void *state) {
    SectorInd candidate_sector;
    int candidate_cell;
    struct _bit_weight weights[NNLAYER_SIZE];
    apply_weights(board, state, weights);
    // now, iterate through them and see the first valid one
    for (int i = 0; i < NNLAYER_SIZE; ++i) {
        int ci = weights[i].bit / 2;
        if (ci >= 90)
            continue;
        candidate_sector = (SectorInd)(ci / 9);
        if (candidate_sector != sector)
            continue;
        candidate_cell = (ci % 9) + 1;
        if (!is_legal(board, candidate_sector, candidate_cell, NULL)) {
            *cell = candidate_cell;
            return 1;
        }
    }
    // give at this point, or th
    // puts("Surrendered at fixed sector!");
    return 0;
}

FixedSectorBrain bot_neural_fixed_sector() { return &fixed_sector; }

static int any_sector(BoardPtr board, SectorInd *sector, int *cell,
                      void *state) {
    SectorInd candidate_sector;
    int candidate_cell;
    struct _bit_weight weights[NNLAYER_SIZE];
    apply_weights(board, state, weights);
    // now, iterate through them and see the first valid one
    for (int i = 0; i < NNLAYER_SIZE; ++i) {
        int ci = weights[i].bit / 2;
        if (ci >= 90)
            continue;
        candidate_sector = (SectorInd)(ci / 9);
        candidate_cell = (ci % 9) + 1;
        if (!is_legal(board, candidate_sector, candidate_cell, NULL)) {
            *sector = candidate_sector;
            *cell = candidate_cell;
            return 1;
        }
    }
    // give up at this point, or th
    // puts("Surrendered at any sector!");
    return 0;
}

AnySectorBrain bot_neural_any_sector() { return &any_sector; }

#undef _to_bit_weights
