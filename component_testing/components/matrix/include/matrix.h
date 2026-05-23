#ifndef PARSE_H
#define PARSE_H
#include "common.h"
typedef struct Matrix {
    float adjacency_matrix[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
} Matrix;

int read_mtx_stdin(Matrix* graph);

int parse_mtx_coordinate(char input_buffer[], Matrix* graph);


float get_weight(const Matrix* graph, int row, int col);

void set_weight(Matrix* graph, int row, int col, float weight);

#endif
