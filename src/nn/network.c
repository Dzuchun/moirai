#include <nn/network.h>
#include <stdio.h>
#include <stdlib.h>

NNInstance NNZeroes(int layers, NNActivationFunction activation) {
    NNInstance res;
    // according to docs, must be all inited to 0
    res.layers = calloc(layers, sizeof(NNLayer));
    res.layers_count = layers;
    res.activation = activation;
    res.tmp_data = calloc(NNLAYER_SIZE, sizeof(float));
    return res;
}

NNInstance NNRandom(int layers, float min, float max,
                    NNActivationFunction activation) {
    NNInstance res;
    res.layers = calloc(layers, sizeof(NNLayer));
    for (int i = 0; i < layers; ++i)
        for (int j = 0; j < NNLAYER_SIZE; ++j)
            for (int k = 0; k < NNLAYER_SIZE; ++k)
                res.layers[i][j][k] =
                    min + (((float)rand()) / RAND_MAX) * (max - min);
    res.layers_count = layers;
    res.activation = activation;
    res.tmp_data = calloc(NNLAYER_SIZE, sizeof(float));
    return res;
}

NNInstance NNDiff(NNInstance *instance, float max_diff, float min, float max) {
    NNInstance res;
    int layers = instance->layers_count;
    float *w;
    res.layers = calloc(layers, sizeof(NNLayer));
    for (int i = 0; i < layers; ++i)
        for (int j = 0; j < NNLAYER_SIZE; ++j)
            for (int k = 0; k < NNLAYER_SIZE; ++k) {
                w = &instance->layers[i][j][k];
                *w = instance->layers[i][j][k];
                *w += ((float)rand() / RAND_MAX - 0.5) * 2;
                if (*w < min)
                    *w = min;
                if (*w > max)
                    *w = max;
            }
    res.layers_count = instance->layers_count;
    res.tmp_data = calloc(NNLAYER_SIZE, sizeof(float));
    res.activation = instance->activation;
    return res;
}

NNInstance NNfread(FILE *fin, NNActivationFunction actvation) {
    NNInstance res;
    int layers_count;
    fread(&layers_count, sizeof(layers_count), 1, fin);
    res.layers_count = layers_count;
    res.layers = calloc(layers_count, sizeof(NNLayer));
    fread(res.layers, sizeof(NNLayer), layers_count, fin);
    res.activation = actvation;
    res.tmp_data = calloc(NNLAYER_SIZE, sizeof(float));
    return res;
}

void NNfwrite(NNInstance *instance, FILE *fout) {
    int layers_count = instance->layers_count;
    fwrite(&layers_count, sizeof(layers_count), 1, fout);
    fwrite(instance->layers, sizeof(NNLayer), layers_count, fout);
}

#define swap(t, a, b)                                                          \
    {                                                                          \
        t _tmp = a;                                                            \
        a = b;                                                                 \
        b = _tmp;                                                              \
    }

void NNapply(NNInstance *instance, float *data) {
    float *tmp = instance->tmp_data, *row, sum;
    for (int l = 0; l < (instance->layers_count); ++l) {
        // for each layer
        for (int r = 0; r < NNLAYER_SIZE; ++r) {
            // for each output
            sum = 0.0;
            row = (instance->layers)[l][r];
            for (int o = 0; o < NNLAYER_SIZE; ++o)
                sum += row[o] * data[o];
            tmp[r] = instance->activation(sum);
        }
        swap(float *, tmp, data);
    }
}

void NNFree(NNInstance *instance) {
    free(instance->layers);
    free(instance->tmp_data);
}

#undef swap
