//
// Created by Wang, Chen on 10/28/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "combine.h"
#include "string.h"

int methodGenerator(int accumulators, int unrollingFactor, char *address);

void unroll2a_combine(vec_ptr v, data_t *dest) {
    int length = vec_length(v);
    int limit = length - 1;
    data_t *d = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    int i;
    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2) {
        x0 = x0 OP d[i];
        x1 = x1 OP d[i + 1];
    }
    /* Finish any remaining elements */
    for (; i < length; i++) {
        x0 = x0 OP d[i];
    }
    *dest = x0 OP x1;
}

int main() {
    for (int j = 1; j <= 12; ++j) {
        for (int i = 1; i <= 12; ++i) {
            char method[30000];
            methodGenerator(i, j, method);
            printf("%s", method);
        }
    }
    vec_ptr vector = new_vec(10);
    int value = 0;
    for (int i = 0; i < 10; i++)
        set_vec_element(vector, i, 5);
    data_t *data = &value;
    unroll2a_combine(vector, data);
    printf("%d", *data);
    return 0;
}