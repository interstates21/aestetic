#include "../includes/doom_nukem.h"

double *getScreenPixels() {
    double *arr;
    arr = (double*)malloc(sizeof(double) * WIDTH * HEIGHT);
    if (!arr)
        print_err("pixels allocation failed");
    return (arr);
}