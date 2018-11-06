//
// Created by StrayBird_ATSH on 05-Nov-18.
//
#include <stdlib.h>
#include "string.h"

int methodGenerator(int accumulators, int unrollingFactor, char *result) {
    strcat(result, "void combine(vec_ptr v, data_t *dest) {\n"
                   "  int length = vec_length(v);\n"
                   "    int limit = length - (");
    char unrollChar[] = "01";
    char accuChar[] = "01";
    itoa(accumulators, accuChar, 10);
    itoa(unrollingFactor, unrollChar, 10);
    if (accumulators < unrollingFactor)
        strcat(result, accuChar);
    else
        strcat(result, unrollChar);
    strcat(result, " - 1);\n"
                   "data_t *d = get_vec_start(v);\n"
                   "data_t x0 = IDENT;\n");
    switch (accumulators) {
        case 12:
            strcat(result, "data_t x11 = IDENT;\n");
        case 11:
            strcat(result, "data_t x10 = IDENT;\n");
        case 10:
            strcat(result, "data_t x9 = IDENT;\n");
        case 9:
            strcat(result, "data_t x8 = IDENT;\n");
        case 8:
            strcat(result, "data_t x7 = IDENT;\n");
        case 7:
            strcat(result, "data_t x6 = IDENT;\n");
        case 6:
            strcat(result, "data_t x5 = IDENT;\n");
        case 5:
            strcat(result, "data_t x4 = IDENT;\n");
        case 4:
            strcat(result, "data_t x3 = IDENT;\n");
        case 3:
            strcat(result, "data_t x2 = IDENT;\n");
        case 2:
            strcat(result, "data_t x1 = IDENT;\n");
        default:
            break;
    }
    strcat(result, "int i;\n");
    strcat(result, "for (i = 0; i < limit; i +=");
    strcat(result, unrollChar);
    strcat(result, ") {\n");
    if (accumulators >= unrollingFactor)
        switch (accumulators) {
            case 12:
                strcat(result, "x11 = x11 OP d[i + 11];\n");
            case 11:
                strcat(result, "x10 = x10 OP d[i + 10];\n");
            case 10:
                strcat(result, "x9 = x9 OP d[i + 9];\n");
            case 9:
                strcat(result, "x8 = x8 OP d[i + 8];\n");
            case 8:
                strcat(result, "x7 = x7 OP d[i + 7];\n");
            case 7:
                strcat(result, "x6 = x6 OP d[i + 6];\n");
            case 6:
                strcat(result, "x5 = x5 OP d[i + 5];\n");
            case 5:
                strcat(result, "x4 = x4 OP d[i + 4];\n");
            case 4:
                strcat(result, "x3 = x3 OP d[i + 3];\n");
            case 3:
                strcat(result, "x2 = x2 OP d[i + 2];\n");
            case 2:
                strcat(result, "x1 = x1 OP d[i + 1];\n");
            default:
                strcat(result, "x0 = x0 OP d[i];\n");
        }
    else
        switch (unrollingFactor) {
            case 12:
                if (accumulators >= 6) {
                    switch (accumulators) {
                        case 11:
                            strcat(result, "x10 = x10 OP d[i + 3];\n");
                        case 10:
                            strcat(result, "x9 = x9 OP d[i + 5];\n");
                        case 9:
                            strcat(result, "x8 = x8 OP d[i + 7];\n");
                        case 8:
                            strcat(result, "x7 = x7 OP d[i + 9];\n");
                        case 7:
                            strcat(result, "x6 = x6 OP d[i + 11];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 11:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 10:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 9:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        case 8:
                            strcat(result, "x4 = x4 OP d[i + 8];\n");
                        case 7:
                            strcat(result, "x5 = x5 OP d[i + 10];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 6:
                            strcat(result, "x5 = x5 OP (d[i+10] OP d[i+11]);\n");
                        case 7:
                            strcat(result, "x4 = x4 OP (d[i+8] OP d[i+9]);\n");
                        case 8:
                            strcat(result, "x3 = x3 OP (d[i+6] OP d[i+7]);\n");
                        case 9:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 10:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 11:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators >= 4) {
                    switch (accumulators) {
                        case 4:
                            strcat(result, "x3 = x3 OP (d[i+9] OP (d[i+10] OP d[i+11]));\n");
                            break;
                        case 5:
                            strcat(result, "x4 = x4 OP d[i+11];\n");
                            strcat(result, "x3 = x3 OP (d[i+9] OP d[i+10]);\n");
                        default:
                            break;
                    }
                    strcat(result, "x2 = x2 OP (d[i+6] OP (d[i+7] OP d[i+8]));\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+8] OP (d[i+9] OP (d[i+10] OP d[i+11])));\n"
                                   "x1 = x1 OP (d[i+4] OP (d[i+5] OP (d[i+6] OP d[i+7])));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP d[i+3])));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+6] OP (d[i+7] OP (d[i+8] OP (d[i+9] OP (d[i+10] OP d[i+11])))));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP d[i+5])))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "(d[i+6] OP (d[i+7] OP (d[i+8] OP (d[i+9] OP (d[i+10] OP d[i+11])))))))))));\n");
                break;
            case 11:
                if (accumulators >= 6) {
                    switch (accumulators) {
                        case 10:
                            strcat(result, "x9 = x9 OP d[i + 3];\n");
                        case 9:
                            strcat(result, "x8 = x8 OP d[i + 5];\n");
                        case 8:
                            strcat(result, "x7 = x7 OP d[i + 7];\n");
                        case 7:
                            strcat(result, "x6 = x6 OP d[i + 9];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 10:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 9:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 8:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        case 7:
                            strcat(result, "x4 = x4 OP d[i + 8];\n");
                        default:
                            strcat(result, "x5 = x5 OP d[i + 10];\n");
                    }
                    switch (accumulators) {
                        case 6:
                            strcat(result, "x4 = x4 OP (d[i+8] OP d[i+9]);\n");
                        case 7:
                            strcat(result, "x3 = x3 OP (d[i+6] OP d[i+7]);\n");
                        case 8:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 9:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 10:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators >= 4) {
                    switch (accumulators) {
                        case 4:
                            strcat(result, "x3 = x3 OP (d[i+9] OP d[i+10]);\n");
                            break;
                        case 5:
                            strcat(result, "x4 = x4 OP d[i+10];\n");
                            strcat(result, "x3 = x3 OP d[i+9];\n");
                        default:
                            break;
                    }
                    strcat(result, "x2 = x2 OP (d[i+6] OP (d[i+7] OP d[i+8]));\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+8] OP (d[i+9] OP d[i+10]));\n"
                                   "x1 = x1 OP (d[i+4] OP (d[i+5] OP (d[i+6] OP d[i+7])));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP d[i+3])));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+6] OP (d[i+7] OP (d[i+8] OP (d[i+9] OP d[i+10]))));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP d[i+5])))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "(d[i+6] OP (d[i+7] OP (d[i+8] OP (d[i+9] OP d[i+10]))))))))));\n");
                break;
            case 10:
                if (accumulators >= 5) {
                    switch (accumulators) {
                        case 9:
                            strcat(result, "x8 = x8 OP d[i + 3];\n");
                        case 8:
                            strcat(result, "x7 = x7 OP d[i + 5];\n");
                        case 7:
                            strcat(result, "x6 = x6 OP d[i + 7];\n");
                        case 6:
                            strcat(result, "x5 = x5 OP d[i + 9];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 9:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 8:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 7:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        case 6:
                            strcat(result, "x4 = x4 OP d[i + 8];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 5:
                            strcat(result, "x4 = x4 OP (d[i+8] OP d[i+9]);\n");
                        case 6:
                            strcat(result, "x3 = x3 OP (d[i+6] OP d[i+7]);\n");
                        case 7:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 8:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 9:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators == 4) {
                    strcat(result, "x3 = x3 OP d[i+9];\n");
                    strcat(result, "x2 = x2 OP (d[i+6] OP (d[i+7] OP d[i+8]));\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+8] OP d[i+9]);\n"
                                   "x1 = x1 OP (d[i+4] OP (d[i+5] OP (d[i+6] OP d[i+7])));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP d[i+3])));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+6] OP (d[i+7] OP (d[i+8] OP d[i+9])));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP d[i+5])))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "(d[i+6] OP (d[i+7] OP (d[i+8] OP d[i+9])))))))));\n");
                break;
            case 9:
                if (accumulators >= 5) {
                    switch (accumulators) {
                        case 8:
                            strcat(result, "x7 = x7 OP d[i + 3];\n");
                        case 7:
                            strcat(result, "x6 = x6 OP d[i + 5];\n");
                        case 6:
                            strcat(result, "x5 = x5 OP d[i + 7];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 8:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 7:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 6:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        case 5:
                            strcat(result, "x4 = x4 OP d[i + 8];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 5:
                            strcat(result, "x3 = x3 OP (d[i+6] OP d[i+7]);\n");
                        case 6:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 7:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 8:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators == 4) {
                    strcat(result, "x3 = x3 OP d[i+8];\n");
                    strcat(result, "x2 = x2 OP (d[i+6] OP d[i+7]);\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+6] OP (d[i+7] OP d[i+8]));\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+5] OP (d[i+6] OP (d[i+7] OP d[i+8])));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP d[i+4]))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "(d[i+6] OP (d[i+7] OP d[i+8]))))))));\n");
                break;
            case 8:
                if (accumulators >= 4) {
                    switch (accumulators) {
                        case 7:
                            strcat(result, "x6 = x6 OP d[i + 3];\n");
                        case 6:
                            strcat(result, "x5 = x5 OP d[i + 5];\n");
                        case 5:
                            strcat(result, "x4 = x4 OP d[i + 7];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 7:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 6:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 5:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 4:
                            strcat(result, "x3 = x3 OP (d[i+6] OP d[i+7]);\n");
                        case 5:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 6:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 7:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+6] OP d[i+7]);\n"
                                   "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+5] OP (d[i+6] OP d[i+7]));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP d[i+4]))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "(d[i+6] OP d[i+7])))))));\n");
                break;
            case 7:
                if (accumulators >= 4) {
                    switch (accumulators) {
                        case 6:
                            strcat(result, "x5 = x5 OP d[i + 3];\n");
                        case 5:
                            strcat(result, "x4 = x4 OP d[i + 5];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 6:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 5:
                            strcat(result, "x2 = x2 OP d[i + 4];\n");
                        case 4:
                            strcat(result, "x3 = x3 OP d[i + 6];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 4:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 5:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 6:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators == 3)
                    strcat(result, "x2 = x2 OP (d[i+5] OP d[i+6]);\n"
                                   "x1 = x1 OP (d[i+3] OP d[i+4]);\n"
                                   "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+4] OP (d[i+5] OP d[i+6]));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP d[i+3]))));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP (d[i+5] OP "
                           "d[i+6]))))));\n");
                break;
            case 6:
                if (accumulators >= 3) {
                    switch (accumulators) {
                        case 5:
                            strcat(result, "x4 = x4 OP d[i + 3];\n");
                        case 4:
                            strcat(result, "x2 = x2 OP d[i + 5];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 5:
                            strcat(result, "x1 = x1 OP d[i + 2];\n");
                        case 4:
                            strcat(result, "x3 = x3 OP d[i + 4];\n");
                        default:
                            break;
                    }
                    switch (accumulators) {
                        case 3:
                            strcat(result, "x2 = x2 OP (d[i+4] OP d[i+5]);\n");
                        case 4:
                            strcat(result, "x1 = x1 OP (d[i+2] OP d[i+3]);\n");
                        case 5:
                            strcat(result, "x0 = x0 OP (d[i] OP d[i+1]);\n");
                        default:
                            break;
                    }
                } else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+3] OP (d[i+4] OP d[i+5]));\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2])));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP (d[i+4] OP d[i+5])))));\n");
                break;
            case 5:
                if (accumulators == 4) {
                    strcat(result,
                           "x3 = x3 OP d[i+4];\n"
                           "x2 = x2 OP d[i+3];\n"
                           "x1 = x1 OP d[i+2];\n"
                           "x0 = x0 OP (d[i] OP d[i+1]);\n");

                }
                if (accumulators == 3) {
                    strcat(result,
                           "x2 = x2 OP d[i+4];\n"
                           "x1 = x1 OP (d[i+2] OP d[i+3]);\n"
                           "x0 = x0 OP (d[i] OP d[i+1]);\n");
                } else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+3] OP d[i+4]);\n"
                           "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2])));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP (d[i+3] OP d[i+4]))));\n");
                break;
            case 4:
                if (accumulators == 3)
                    strcat(result,
                           "x2 = x2 OP d[i+3];\n"
                           "x1 = x1 OP d[i+2];\n"
                           "x0 = x0 OP (d[i] OP d[i+1]);\n");
                else if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP (d[i+2] OP d[i+3]);\n"
                           "x0 = x0 OP (d[i] OP d[i+1]));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP (d[i+2] OP d[i+3])));\n");
                break;
            case 3:
                if (accumulators == 2)
                    strcat(result,
                           "x1 = x1 OP d[i+2];\n"
                           "x0 = x0 OP (d[i] OP d[i+1]));\n");
                else
                    strcat(result,
                           "x0 = x0 OP (d[i] OP (d[i+1] OP d[i+2]));\n");
                break;
            case 2:
                strcat(result,
                       "x0 = x0 OP (d[i] OP d[i+1]);\n");
                break;
            default:
                break;
        }
    strcat(result, "}\n"
                   "for (; i < length; i++) {\n"
                   "        x0 = x0 OP d[i];\n"
                   "}\n");
    switch (accumulators) {
        case 12:
            strcat(result, "x10 = x10 OP x11;\n");
        case 11:
            strcat(result, "x9 = x9 OP x10;\n");
        case 10:
            strcat(result, "x8 = x8 OP x9;\n");
        case 9:
            strcat(result, "x7 = x7 OP x8;\n");
        case 8:
            strcat(result, "x6 = x6 OP x7;\n");
        case 7:
            strcat(result, "x5 = x5 OP x6;\n");
        case 6:
            strcat(result, "x4 = x4 OP x5;\n");
        case 5:
            strcat(result, "x3 = x3 OP x4;\n");
        case 4:
            strcat(result, "x2 = x2 OP x3;\n");
        case 3:
            strcat(result, "x1 = x1 OP x2;\n");
        case 2:
            strcat(result, "x0 = x0 OP x1;\n");
        default:
            break;
    }
    strcat(result, "}\n");
    return 0;
}