//
// Created by Wang, Chen on 10/28/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/time.h>
#include "combine.h"
#include "string.h"

int methodGenerator(int accumulators, int unrollingFactor, char *address);

void combine(vec_ptr v, data_t *dest);

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
    for (int j = 1; j <= 12; j++)
        for (int i = 1; i <= 12; i++) {
            char method[10000] = "";
            char address[2000] = "";
            char unroll[4] = "";
            char accum[4] = "";
            strcat(address, "/media/straybird/LENOVO/Documents/Introduction to Computer System/Lab/"
                            "Lab2 Unrolling&Accumulating/IntermediateFiles/unroll");
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

void generateSo() {
    printf("The generating So file process.");
    for (int j = 1; j <= 12; ++j) {
        for (int i = 1; i <= 12; ++i) {
            char fileName[1000] = {
                    "\"/media/straybird/LENOVO/Documents/Introduction to Computer System/Lab/"
                    "Lab2 Unrolling&Accumulating/IntermediateFiles/unroll"};
            char unroll[4] = {""};
            char accum[4] = {""};
            strcat(fileName, "");
            sprintf(unroll, "%d", i);
            strcat(fileName, unroll);
            strcat(fileName, "_accu");
            sprintf(accum, "%d", j);
            strcat(fileName, accum);
            char arg3[200];
            strcpy(arg3, fileName);
            strcat(arg3, ".so\" ");
            char arg4[200];
            strcpy(arg4, fileName);
            strcat(arg4, ".c\"");
            char argument[1000] = "gcc -shared -fpic -o ";
            strcat(argument, arg3);
            strcat(argument, arg4);
            system(argument);
        }
    }
}

void linkRun() {
    FILE *file = fopen("./dataOut.data", "w");
    fprintf(file, "1 2 3 4 5 6 7 8 9 10 11 12\n");
    for (int j = 1; j <= 12; j++) {
        fprintf(file, "%d ", j);
        for (int i = 1; i <= 12; i++) {
            char address[2000] = "";
            char unroll[4] = "";
            char accum[4] = "";
            strcat(address, "/media/straybird/LENOVO/Documents/Introduction to Computer System/Lab/"
                            "Lab2 Unrolling&Accumulating/IntermediateFiles/unroll");
            sprintf(unroll, "%d", i);
            strcat(address, unroll);
            strcat(address, "_accu");
            sprintf(accum, "%d", j);
            strcat(address, accum);
            strcat(address, ".so");
            void *handle;
            long (*combine)(vec_ptr, data_t *);
            char *error;
            handle = dlopen(address, RTLD_GLOBAL | RTLD_NOW);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(1);
            }
            combine = dlsym(handle, "combine");
            if ((error = dlerror()) != NULL) {
                fprintf(stderr, "%s\n", error);
                exit(1);
            }

            vec_ptr vector = new_vec((long) 1e6);
            int value = 0;
            for (int i1 = 0; i1 < 1e6; i1++)
                set_vec_element(vector, i1, 5);
            data_t *data = &value;
            double dump = 100;
            for (int j1 = 0; j1 < 1e6; ++j1)
                dump *= j1;
            long timeConsumed1 = combine(vector, data);
            vector = new_vec((long) 1e5);
            value = 0;
            for (int i1 = 0; i1 < 1e5; i1++)
                set_vec_element(vector, i1, 5);
            data = &value;
            dump = 100;
            for (int j1 = 0; j1 < 1e6; ++j1)
                dump *= j1;
            long timeConsumed2 = combine(vector, data);
            if (dlclose(handle) < 0) {
                fprintf(stderr, "%s\n", dlerror());
                exit(1);
            }
            printf("Time consumed1 is %ld\n", timeConsumed1);
            printf("Time consumed2 is %ld\n", timeConsumed2);
            fprintf(file, "%f ", (double) (timeConsumed1 - timeConsumed2) * 2600 / 9e5);
            fflush(file);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    linkRun();
}