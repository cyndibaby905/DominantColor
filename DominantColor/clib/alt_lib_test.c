#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "alt_lib.h"
#include "azzert.h"

int main(int argc, char *argv[]) {
    int *clusters;
    unsigned long int ms;
    size_t k = 16, n = 100;
    clock_t diff, start = clock();
    DDArray *darr, *centroids;

    if (argc >= 2 && sscanf(argv[1], "%zd", &n) != 1) {
        n = 100;
    }

    printf("n: %zd\n", n);

    darr = populatedDDArray(n, 3);
    centroids = createCentroids(9000, k, darr);
    clusters = kMeans(darr->data, darr->n, darr->m, centroids->n, 0.01, centroids->data);

#ifdef DEBUG
    size_t i;
    for (i = 0; i < k; ++i) {
        printf("%d\n", clusters[i]); 
    }
#endif

    free(clusters);

#ifdef DEBUG
    printDDArray(centroids);
    printDDArray(darr);
#endif // DEBUG

    destroyDDArray(darr);
    destroyDDArray(centroids);

    diff = clock() - start;
    ms = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time: %ld ms diff: %ld\n", ms, diff);

    return 0;
}
