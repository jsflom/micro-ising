#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "v2.h"
#include "matrix.h"
#include "common.h"

Model model;

int main(int argc, char** argv){
    srand(time(NULL));
    model.timestep = .05;
    model.max_time = 800;
    model.graph_size = read_mtx_stdin(&(model.graph));
//     for(int i = 0; i < model.graph_size; ++i){
//         for(int j = 0; j < model.graph_size; ++j){
//             printf("%f\t", get_weight(&(model.graph), i, j));
//         }
//         printf("\n");
//     }
    get_random_configuration(&model);
    for(int i = 0; i < 2; ++i){
        get_random_cube(&model);
        propagate(&model);
    }
    for(int i = 0; i < model.graph_size; ++i){
        printf("%d\t", model.state.S[i]);
    }
    printf("\n");
    return 0;
}
