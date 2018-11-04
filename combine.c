//
// Created by Wang, Chen on 10/28/18.
//
#include <stdio.h>
#include "combine.h"

data_t x0 = IDENT;
data_t x1 = IDENT;
data_t x2 = IDENT;
data_t x3 = IDENT;
data_t x4 = IDENT;
data_t x5 = IDENT;
data_t x6 = IDENT;
data_t x7 = IDENT;
data_t x8 = IDENT;
data_t x9 = IDENT;
data_t x10 = IDENT;
data_t x11 = IDENT;

void unroll2a_combine(vec_ptr v, data_t *dest, int unrollingDegree, int accumulator) {
    long length = vec_length(v);
    long limit = length - (unrollingDegree - 1);
    data_t *d = get_vec_start(v);
    long i;
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += unrollingDegree) {
        x0 = x0 OP d[i];
        x1 = x1 OP d[i + 1];
    }
//    GET_VEC_ELEMENT(v, 1, d);
    /* Finish any remaining elements */
    for (; i < length; i++)
        x0 = x0 OP d[i];
    *dest = x0 OP x1;
}

int main() {
    vec_ptr vector = new_vec(10);
    int value = 0;
    for (int i = 0; i < 10; i++)
        set_vec_element(vector, i, 5);
    data_t *data = &value;
    unroll2a_combine(vector, data, 2, 2);
    printf("%d", *data);
    return 0;
}