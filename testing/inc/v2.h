#ifndef V2_H
#define V2_H
#include <stdint.h>
#include "common.h"
#include "matrix.h"

typedef struct State {
    // metadata?
    float X[MAX_GRAPH_SIZE];
    int8_t S[MAX_GRAPH_SIZE];
} State;

typedef struct Model {
    Matrix graph;
    float timestep;
    int max_time;
    int graph_size;
    State state;
} Model;


void propagate(Model* model);

void step(Model* model);

void get_change(Model* model, float* DX);

void update_state(Model* model, float* DX);

int sign(float x1, float x2);

void get_random_configuration(Model* model);

void get_random_cube(Model* model);

#endif
