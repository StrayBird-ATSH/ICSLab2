//
// Created by Wang, Chen on 10/28/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "combine.h"
#include "string.h"

int methodGenerator(int accumulators, int unrollingFactor, char *address);

void unroll2a_combine(vec_ptr v, data_t *dest) {
    long length = vec_length(v);
    long limit = length - 1;
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

void generateC() {
    for (int j = 1; j <= 12; ++j) {
        for (int i = 1; i <= 12; ++i) {
            char method[10000] = {""};
            char address[1000] = {""};
            char unroll[2] = {""};
            char accum[2] = {""};
            strcat(address, "/media/wang-chen/Documents/Introduction to Computer System/"
                            "Lab/Lab2 Unrolling&Accumulating/unroll");
            sprintf(unroll, "%d", i);
            strcat(address, unroll);
            strcat(address, "_accu");
            sprintf(accum, "%d", j);
            strcat(address, accum);
            strcat(address, ".c");
            methodGenerator(j, i, method);
            FILE *file = fopen(address, "w");
            fputs(method, file);
            fflush(file);
            fclose(file);
        }
    }
}

void generateSo() {
    for (int j = 1; j <= 12; ++j) {
        for (int i = 1; i <= 12; ++i) {
            char fileName[1000] = {
                    "/media/wang-chen/Documents/Introduction to Computer System/"
                    "Lab/Lab2 Unrolling&Accumulating/unroll"};
            char unroll[2] = {""};
            char accum[2] = {""};
            strcat(fileName, "");
            sprintf(unroll, "%d", i);
            strcat(fileName, unroll);
            strcat(fileName, "_accu");
            sprintf(accum, "%d", j);
            strcat(fileName, accum);
            char arg3[200];
            strcpy(arg3, fileName);
            strcat(arg3, ".so ");
            char arg4[200];
            strcpy(arg4, fileName);
            strcat(arg4, ".c");
            char *argument = "-shared -fpic -o ";
            strcat(argument, arg3);
            strcat(argument, arg4);
            execve("gcc", &argument, NULL);
        }
    }
}

int main() {
    generateC();
    vec_ptr vector = new_vec(10);
    int value = 0;
    for (int i = 0; i < 10; i++)
        set_vec_element(vector, i, 5);
    data_t *data = &value;
    unroll2a_combine(vector, data);
    printf("%d", *data);
    return 0;
}