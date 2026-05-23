#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "esp_random.h"
#include "common.h"
#include "v2.h"


// State and Model definition for reference:
// typedef struct State {
//     // metadata?
//     float X[MAX_GRAPH_SIZE];
//     int8_t S[MAX_GRAPH_SIZE];
// } State;
// 
// typedef struct Model {
//     Matrix graph;
//     float timestep;
//     int max_time;
//     int graph_size;
//     State state;
// } Model;

void propagate(Model* model){
    for(int i = 0; i < model->max_time; ++i){
        step(model);
    }
}

void step(Model* model){
   float DX[MAX_GRAPH_SIZE] = {0};
   get_change(model, DX);
   update_state(model, DX);
}

void get_change(Model* model, float* DX){
   for(int i = 0; i < model->graph_size; ++i){
        float xnode = model->state.X[i];
        for(int j = 0; j < model->graph_size; ++j){
            if(i == j){
                continue;
            } else {
                DX[i] += model->state.S[j] * sign(xnode, model->state.X[j]) 
                    * get_weight(&(model->graph), i, j);
            }
        }
   }
   for(int i = 0; i < model->graph_size; ++i){
       DX[i] *= model->state.S[i];
   }
}

void update_state(Model* model, float* DX){
    for(int i = 0; i < model->graph_size; ++i){
        model->state.X[i] += model->timestep * DX[i];
        if(model->state.X[i] > 1){
            model->state.X[i] -= 2;
            model->state.S[i] *= -1;
        } else if (model->state.X[i] < -1){
            model->state.X[i] += 2;
            model->state.S[i] *= -1;
        }
    }
}

int sign(float x1, float x2){
    return ((x1 - x2) > 0) - ((x1 - x2) < 0);
}

// bernoulli sequence
void get_random_configuration(Model* model){
    for(int i = 0; i < model->graph_size; ++i){
        model->state.S[i] = (((float)esp_random() / (float)(UINT32_MAX)) > .5) ? 1 : -1;
    }
}

 
// function get_random_cube(Nvert::Int, side::Float64)::FVector
//     return side .* (rand(Float64, Nvert) .- 0.5)
// end

// returns a random point on an n-d unit cube (makes sense, i swear!)
// WARNING - HARDCODED DOMAN (1.2)
void get_random_cube(Model* model){
    for(int i = 0; i < model->graph_size; ++i){
        model->state.X[i] = 1.2 * ((float)esp_random() / (float)(UINT32_MAX)) - .5;
    }
}
