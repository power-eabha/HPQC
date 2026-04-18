#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./time_write <number_of_lines>\n");
        return 1;
    }

    int n = atoi(argv[1]);

    FILE *file = fopen("data/sample_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    clock_t start_time = clock();

    for (int i = 0; i < n; i++) {
        fprintf(file, "This is line %d\n", i);
    }

    fclose(file);

    clock_t end_time = clock();
    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Wrote %d lines to data/sample_data.txt\n", n);
    printf("Runtime: %.6f seconds\n", run_time);

    return 0;
}
