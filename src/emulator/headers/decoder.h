//
// Created by crist on 5/28/2020.
//

#ifndef ARM11_10_DECODER_H
#define ARM11_10_DECODER_H

#include "../../structures.h"

void decode_data_process(State *current_state);

void decode_single_data_transfer(State *current_state);

void decode_multiply(State *current_state);

void decode_branch(State *current_state);

#endif //ARM11_10_DECODER_H
