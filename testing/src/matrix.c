#include <stdio.h>
#include "matrix.h"
#include "common.h"

// very naive - assume one line header and no comments
int read_mtx_stdin(Matrix* graph){
    char buffer[64];
   
    // matrix market header
    fgets(buffer, sizeof(buffer), stdin); 

    // matrix size data
    int graph_size;
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &graph_size);

    
    
    // no error checking currently
    for(;;){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            return graph_size;
        } else if(parse_mtx_coordinate(buffer, graph) == -1){
            return -1;
        }
    }
}


// requires: sparse symmetrix matrix
int parse_mtx_coordinate(char *input_buffer, Matrix* graph){
    int i, j;
    float weight;
    if(sscanf(input_buffer, "%d %d %f", &i, &j, &weight) != 3){
        return -1;
    }
    set_weight(graph, i - 1, j - 1, weight);
    set_weight(graph, j - 1, i - 1, weight);
    return 0;
}

float get_weight(const Matrix* graph, int row, int col){
    return graph->adjacency_matrix[row][col];
}

void set_weight(Matrix* graph, int row, int col, float weight){
    graph->adjacency_matrix[row][col] = weight;
}
