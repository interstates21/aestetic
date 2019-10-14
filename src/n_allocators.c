#include "../includes/doom_nukem.h"

double *getScreenPixels() {
    double *arr;
    size_t memorySize;

    memorySize = sizeof(double) * WIDTH * HEIGHT;
    arr = (double*)pureMalloc(memorySize, "pixels allocation failed");
    return (arr);
}

void *pureMalloc(size_t size, const char *err) {
    void *data = malloc(size);
    if (!data) {
        ft_putendl_fd("malloc has failed\n", 2);
        exit(1);
    }
    return(data);
}