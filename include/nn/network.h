#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>

typedef float (*NNActivationFunction)(float);

#define NNLAYER_SIZE (8 * 24)

typedef float NNLayer[NNLAYER_SIZE][NNLAYER_SIZE];

struct _network {
    NNLayer *layers;
    int layers_count;
    NNActivationFunction activation;
    float *tmp_data;
};
typedef struct _network NNInstance;

// Creates new NN filled with zeroes
NNInstance NNZeroes(int layers, NNActivationFunction activation);

// Creates new NN filled with random values in range [min; max[
NNInstance NNRandom(int layers, float min, float max,
                    NNActivationFunction activation);

// Creates a near-copy of the previous network
NNInstance NNDiff(NNInstance *instance, float max_diff, float min, float max);

// Attempts to read NN from file
NNInstance NNfread(FILE *fin, NNActivationFunction activation);

// Writes NN to file
void NNfwrite(NNInstance *instance, FILE *fout);

// Expects array of size NNLAYER_SIZE
void NNapply(NNInstance *instance, float *data);

// Should be called, once not needed anymore
//
// Should not be used after that
void NNFree(NNInstance *instance);

#endif
